class Download
  ERL_VERSION_MAGIC   = 131
  ERL_NIL_EXT         = 'j'
  ERL_SMALL_TUPLE_EXT = 'h'
  ERL_ATOM_EXT        = 'd'
  ERL_BINARY_EXT      = 'm'
  ERL_INTEGER_EXT     = 'b'
  ERL_CONTENT_TYPE    = "application/x-erlang-binary"
  MAXATOMLEN          = 255

  attr_accessor :buffer, :request, :first_packet, :socket, :path

  def initialize(serial, path)
    @serial  = serial
    @path    = path
    @version = "0.42"
  end

  #  0: Success
  # -1: Commnucation error
  # -2: Mapreduce response error
  # -3: IO Error
  def riak_mapreduce_request(socket, company_name, file_name, crc, current_app, logical_number)
    @socket, @buffer, @request, @first_packet = socket, "", "", ""
    key = "#{company_name}_#{file_name}"

    ei_encode_version                # version
    ei_encode_list_header(3)         # mapreduce with 3 tuples
    ei_encode_tuple_header(2)        # tuple 1 inputs
    ei_encode_atom("inputs")         # atom inputs
    ei_encode_list_header(1)         # list inputs
    ei_encode_tuple_header(2)        # tuple contendo 2 elementos binarios, bucket and key
    ei_encode_binary("assets")       # elemento binario bucket
    ei_encode_binary(key)            # elemento binario key
    ei_encode_list_header(0)         # fim da list do inputs

    ei_encode_tuple_header(2)        # tuple 2: query
    ei_encode_atom("query")          # atom query
    ei_encode_list_header(1)         # list da query
    ei_encode_tuple_header(4)        # tuple contendo 4 elementos, { map, {modfun,Module,Function}, args, true }
    ei_encode_atom("map")            # primeiro elemento, atom type
    ei_encode_tuple_header(3)        # segundo elemento, nova tuple contendo 3 atoms
    ei_encode_atom("modfun")         # primeiro atom do segundo elemento, modfun
    ei_encode_atom("walk")           # segundo atom do segundo elemento, Module
    ei_encode_atom("get_asset")      # terceiro atom do segundo elemento, Function

    ei_encode_list_header(7)         # terceiro elemento, uma list com parametros do walk
    ei_encode_binary(@serial)        # elemento binario serialterminal
    ei_encode_binary(@version)       # elemento binario versao walk
    ei_encode_binary(file_name)      # elemento binario nomeaplicativo
    ei_encode_binary(crc)            # elemento binario crc aplicativo
    ei_encode_binary("")             # elemento binario buffer do posxml
    ei_encode_binary(logical_number) # elemento binario numero do terminal
    ei_encode_binary(current_app)    # elemento binario nome do aplicativo que esta sendo executado
    ei_encode_list_header(0)         # fim da list com parametros do walk

    ei_encode_atom("true")           # quarto elemento, atom true
    ei_encode_list_header(0)         # fim da list da query

    ei_encode_tuple_header(2)        # tuple 3: timeout
    ei_encode_atom("timeout")        # atom timeout
    ei_encode_long(5000)             # integer timeout
    ei_encode_list_header(0)         # fim da list do mapreduce contendo 3 tuples

    mount_request                    # add request to protocol buffers message

    # Send Request
    socket.write(@request)

    # Read header
    return -1 if (socket.read(4).size <= 0)

    response_size, @first_packet = get_response_size

    if response_size > 1024
      @first_packet = @first_packet + socket.read(1024)
    else
      @first_packet = @first_packet + socket.read(response_size)
    end

    return -2 unless binary_valid?

    return_code = @first_packet[7].to_s.unpack("C*").first
    file_size   = @first_packet[9..12].to_s.unpack("N*").first

    return -3 if (partial_download_to_store(file_name, response_size, file_size) < 0)

    # receive 6A
    @socket.read(1) if response_size > 1024

    return_code
  ensure
    @socket.close
  end

  alias :request :riak_mapreduce_request

  def get_response_size
    binary_size, packet, found = "", "", false
    @socket.read(8).each_char do |str|
      if found || str.unpack("H*").first == "83"
        packet << str
        found = true
      else
        binary_size << str
      end
    end

    size = ljust(4, binary_size).to_s.unpack("V*").first
    [size, packet]
  end

  def makelong(a, b)
    (a & 0xffff) | ((b & 0xffff) << 16)
  end

  def makeword(a, b)
    (a & 0xff) | ((b & 0xff) << 8)
  end

  def partial_download_to_store(file_name, response_size, file_size)
    begin
      tmp  = posxml_file_path("tmp_#{file_name}")
      file = File.open(tmp, "w+")

      if (response_size > 1024)
        file.write(@first_packet[13..-1])
        downloaded = 1024
        while(downloaded < (response_size - 1))
          if (to_download = response_size - downloaded) > 1024
            to_download = 1024
          else
            to_download -= 1 # because of 6A
          end
          file.write(socket.read(to_download))
          downloaded += to_download
        end
      else
        # -2 because of 6A
        downloaded = file.write(@first_packet[13..-2])
      end

      file.close
      File.rename(tmp, posxml_file_path(file_name))
      downloaded
    rescue
      -1
    end
  end

  def put(value)
    @buffer << value
  end

  def put8(value)
    @buffer << value
  end

  def put32be(value)
    @buffer << [value].pack("N")
  end

  def put16be(value)
    @buffer << [value].pack("n")
  end

  def ei_encode_version
    put8(ERL_VERSION_MAGIC.chr)
  end

  def ei_encode_list_header(arity)
    put8(ERL_NIL_EXT)
    put32be(arity) if arity > 0
  end

  def ei_encode_tuple_header(arity)
    # if (arity <= 0xff) ERL_SMALL_TUPLE_EXT else ERL_LARGE_TUPLE_EXT
    put8(ERL_SMALL_TUPLE_EXT)
    put8(arity.chr);
  end

  # TODO: Check why MAXATOMLEN
  def ei_encode_atom(value)
    value.size > MAXATOMLEN ? len = MAXATOMLEN : len = value.size
    put8(ERL_ATOM_EXT)
    put16be(len)
    put(value)
  end

  def ei_encode_binary(value)
    put8(ERL_BINARY_EXT)
    put32be(value.size)
    put(value)
  end

  def ei_encode_long(value)
    put8(ERL_INTEGER_EXT)
    put32be(value)
  end

  def mount_request
    request_size   = [buffer.size].pack("s") + "\x01"

    put8("\x12")
    put8("\x1b")
    @request = [0x00, 0x00, 0x00, 0x00, 0x017, 0x0A].pack("c*")
    @request << "#{request_size}#{buffer}#{ERL_CONTENT_TYPE}"
    @request = [@request.size].pack("N") + @request[3..-1]
  end

  def binary_valid?
    if (@first_packet[0].unpack("H*").first == "83" && @first_packet[1] == "\x6c" && @first_packet[2] == "\x00" && @first_packet[5] == "\x02")
      true
    else
      false
    end
  end

  # MRuby do not support String#ljust
  # TODO: duplicated from lib/variable.rb
  def ljust(size, string)
    if size > string.size
      string = string + ("\x00" * (size - string.size))
    end
    string
  end

  private
  # TODO: repeated code from posxml_parser.rb
  def posxml_file_path(file_name)
    "#{path}#{file_name}"
  end
end
