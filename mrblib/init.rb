
class String
  def chuncks(number)
    array = []
    current = 0
    len =  self.size / number
    len += 1 if (self.size % number) != 0
    len.times do |n|
      array << self[current..(current + number - 1)]
      current += number
    end
    array
  end
end

module TestRobotRock
  def self.test_emv
    Device::Display.clear
    puts "Before"
    getc
    Device::Display.clear
    puts "Result #{PAX::EMV.core_init.inspect}"
    getc
  end

  def self.test_display_clear
    Device::Display.clear
    puts "1asdfasdf"
    puts "2asdfasdf"
    puts "3asdfasdf"
    puts "4asdfasdf"
    getc
    Device::Display.clear
    puts "5asdfasdf"
    getc

    Device::Display.clear
    Device::Display.puts "1asdfasdf"
    Device::Display.puts "2asdfasdf"
    Device::Display.puts "3asdfasdf"
    Device::Display.puts "4asdfasdf"
    getc
    Device::Display.clear
    Device::Display.puts "5asdfasdf"
    getc

    Device::Display.clear
    Device::Display.print "1asdfasdf"
    Device::Display.print "2asdfasdf"
    Device::Display.print "3asdfasdf"
    Device::Display.print "4asdfasdf"
    getc
    Device::Display.clear
    Device::Display.print "5asdfasdf"
    getc
  end

  def self.test_execute
    puts Time.now
    Device::Runtime.execute("global.mrb")
    puts Time.now
  end

  def self.test_zip
    Device::Display.clear
    puts "Preparation to zip"

    test = File.open("test.txt", "w+")
    test.write("AAAAAAAAAAAAAA1")
    test.close

    test2 = File.open("test2.txt", "w+")
    test2.write("BBBBBBBBBBBBBB2")
    test2.close

    Device::Display.clear
    puts "Before zip"
    getc
    puts Miniz.zip("test.zip", "test.txt", "test2.txt")
    getc

    puts "Before unzip"
    getc
    puts Miniz.unzip("test.zip", "./mrb")
    getc

    puts "Before Open"
    getc
    puts File.open("./mrb/test/test.txt").read
    getc
  end

  def self.beep
    Device::Audio.beep(3, 2000)
    getc
  end

  def self.test_io_read_card
    Device::Display.clear
    fd = IO.sysopen("/dev/msr")
    card = IO.open(fd, "r")
    p card.fileno
    sleep 4
    value = ""
    begin
      loop do
        value << card.read(1)
      end
    rescue
      p value.size
    end
    sleep 2
    p value.split("\n").size
    sleep 2
    track1 = value.split("\n")[1]
    track1_bin = track1.unpack("C*").collect{|a| a.to_s(2)}.join
    # Track 2
    p track1_bin.chuncks(5).compact.collect{ |v| str = (v[1..-1].reverse.to_i(2) + 48).chr; str }.join
    # Track 1
    p track1_bin.chuncks(7).compact.collect{ |v| str = (v[1..-1].reverse.to_i(2) + 32).chr; str }.join

    sleep 10
    card.close
    asdf
  end

  def self.test_network_gprs_socket
    puts "=" * 20
    puts "Init #{Network.init(:gprs, apn: 'claro.com.br', user: 'claro.com.br', pass: 'claro.com.br')}"
    puts "Connect #{Network.connect}"
    iRet = 1
    while(iRet == 1)
      puts("Connected? #{iRet = Network.connected?}")
    end

    puts "=" * 20
    puts "Ping #{Network.ping("nas.scalone.com.br", 10000)}   "

    puts "=" * 20
    puts "TCP #{(tcp = TCPSocket.new('switch-staging.cloudwalk.io', 8000)).inspect}"
    puts "Send #{tcp.send('303132', 0)} "
    puts "Recv #{tcp.recv(10)} "
    puts "Closed? #{tcp.closed?}"
    puts "Close #{tcp.close} "
    puts "Closed? #{tcp.closed?}"
    puts "Disconnect #{Network.disconnect}"
  end

  def self.test_network_wifi_socket
    Device::Display.clear
    puts "=" * 20
    #Device::Setting.authentication = "wpa2_psk"
    Device::Setting.authentication = "wpawpa2psk"
    Device::Setting.password       = "planobesemfio"
    Device::Setting.essid          = "PlanoBe"
    #Device::Setting.password       = "ibexes0057"
    #Device::Setting.essid          = "Telemovel"
    #Device::Setting.password       = "desgracapelada"
    #Device::Setting.essid          = "Barril do Chaves"
    Device::Setting.channel        = "0"
    Device::Setting.cipher         = Device::Network::PARE_CIPHERS_TKIP
    Device::Setting.mode           = Device::Network::MODE_STATION

    puts "Attach #{Device::Network.attach}"
    puts "=" * 20

    puts "Ping #{Network.ping("192.168.1.127", 3000)}   "
    puts "NAS Ping #{Network.ping("nas.scalone.com.br", 10000)}   "
    getc
    self.test_http
    asdfasdf
  end

  def self.test_http
    p SimpleHttp.new("http", "google.com", 80).request("GET", "/", {'User-Agent' => "test-agent"})
    getc
  end

  def self.test_https
    p SimpleHttp.new("https", "google.com", 443).request("GET", "/", {'User-Agent' => "test-agent"})
    getc
  end

  def self.test_ssl
    Device::Display.clear
    socket = TCPSocket.new('switch-staging.cloudwalk.io', 31416)
    entropy = PolarSSL::Entropy.new
    ctr_drbg = PolarSSL::CtrDrbg.new(entropy)
    ssl = PolarSSL::SSL.new
    ssl.set_endpoint(PolarSSL::SSL::SSL_IS_CLIENT)
    ssl.set_authmode(PolarSSL::SSL::SSL_VERIFY_NONE)
    ssl.set_rng(ctr_drbg)
    ssl.set_socket(socket)
    ret = ssl.handshake
    puts "After Handshake #{ret}"
    p test_handshake(ssl, "200-200-200")
    getc
  end

  def self.test_generate_qrcode
    msg = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua."
    qr  = QR.new(msg)
    result   = qr.generate
    expected = "BM\006\002\000\000\000\000\000\000>\000\000\000(\000\000\0009\000\000\0009\000\000\000\001\000\001\000\000\000\000\000\310\001\000\000\304\016\000\000\304\016\000\000\002\000\000\000\002\000\000\000\377\377\377\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\017\354\000r\356\351\230\000\b\"cJD@\020\000\v\251S\271\211\317\270\000\v\244\201:\t\037\250\000\v\257k\377\273\217\230\000\b!\032b\333\270\220\000\017\340\314\253\b\212\270\000\000\t\222b\225X\310\000\016 4>\273\317\220\000\a\002\226w\213\212\000\000\004h6\327\215\206\370\000\006C\212b\001\000H\000\r\361\344e\372\240\020\000\n\312\374\312\275\313\230\000\005?\233\2173/\230\000\tD\304\001\273\270X\000\n=\354G\021\b\000\000\a\000~\2273/\210\000\001tj\177\201\037\370\000\001\236 \363@\210P\000\017!\270\232\373\357\030\000\006\321\274I\215\226\300\000\r\372\313\376\211\217\230\000\v\212\304c\f\030\310\000\f\256\333+\273\212\210\000\n\215\006c\331\250\220\000\000\373\017\277\210\237\270\000\nP\322\035\035@X\000\t5\334\036\371\364\310\000\006\e\207\r\334\265\200\000\017w\021\360\356\360H\000\a\227|\000D@8\000\f\266\240z\356\343\220\000\004\emXD\\\220\000\004w\241\365\031Y8\000\r\300QI\025\001\330\000\t\375\257\236\213\243\310\000\006E\032\017\331\215\230\000\003\251=\021\235\004\310\000\002[\224XA\b8\000\n\243\360?\277\350\220\000\000\002\260\243\237\340\000\000\017\352\252\252\252\253\370\000\b&#\243jb\b\000\v\254\233>\367\302\350\000\v\245\241,B\022\350\000\v\242\264\3125\032\350\000\b/\201\364\314\272\b\000\017\342\312tD\v\370\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
    Device::Display.print("QR Test #{expected == result}", 2)

    file = File.open("qrcode.bmp", "w")
    file.write result
    file.close
    Device::Display.print("File Save", 3)
    getc
  end

  def self.test_print_bitmap
    Device::Display.clear
    puts "Before print"
    getc
    Device::Display.print_bitmap("./qrcode.bmp", 0, 0)
    getc
  end

  def self.fib(n)
    return n if n < 2
    fib(n-2) + fib(n-1)
  end

  def self.test_fib
    puts Time.now
    puts "Fib exec #{fib(25)}"
    puts Time.now
  end

  def self.test_file
    puts "Start"
    f = File.open('test', 'w')
    puts "File: #{f.inspect}"
    puts "write #{f.write('MALUCO')}"
    puts "close #{f.close}"
    k = File.open('test', 'r')
    puts "File2: #{k.inspect}"
    puts "read: #{k.read}"
    puts "close: #{k.close}"
  end

  def self.test_network_gprs
    puts "=" * 20
    puts "Init #{Network.init(:gprs, apn: 'claro.com.br', user: 'claro.com.br', pass: 'claro.com.br')}"
    puts "Connect #{Network.connect}"
    iRet = 1
    while(iRet == 1)
      puts("Connected? #{iRet = Network.connected?}")
    end
    puts "Disconnect #{Network.disconnect}"
  end

  def self.test_print
    puts "Start"
    puts true.to_s
    puts "#{false}"
    Kernel.puts "\nAAAAAAA"
    Kernel.puts true
    puts 1
    puts true
    puts 'asdfasdf'
    puts false
  end

  def self.test_get_string
    puts "Start"
    string = get_string(1, 10)
    puts "End"
    getc
    Device::Display.clear
    puts "Result"
    puts string
    getc
  end

  def self.test_getc
    puts "Start"
    puts Kernel.getc
    puts Kernel.getc
    puts IO.getc
    puts "End"
  end

  def self.test_read_card
    puts "Start"
    p IO.read_card(5000)
    p IO.getc
    puts "End"
  end

  def self.test_require
    puts "before require"
    require 'TEST1.MRB'
    sleep 5
    require 'TEST2.RB'
    sleep 5
  end

  def self.test_display_clean
    puts "KKKKKKKKKKKKK"
    puts "KKKKKKKKKKKKK"
    puts "KKKKKKKKKKKKK"
    puts "KKKKKKKKKKKKK"
    puts "KKKKKKKKKKKKK"
    puts "KKKKKKKKKKKKK"
    puts "KKKKKKKKKKKKK"
    puts "KKKKKKKKKKKKK"
    puts "KKKKKKKKKKKKK"
    puts "KKKKKKKKKKKKK"
    p IO.getc
    IO.display_clean
    p IO.getc
  end

  def self.test_connect_gprs
    puts "=" * 26
    puts "Init #{Network.init(:gprs, apn: 'claro.com.br', user: 'claro.com.br', pass: 'claro.com.br')}"
    puts "Connect #{Network.connect}"
    iRet = 1
    while(iRet == 1)
      puts("Connected? #{iRet = Network.connected?}")
      sleep 1
    end
  end

  def self.test_socket
    puts "=" * 25
    #switch-staging.cloudwalk.io
    puts "TCP #{(socket = TCPSocket.new('54.232.125.226', 31415)).inspect}"
    getc
    socket
  end

  def self.test_handshake(socket, serial_terminal)
    handshake = "#{serial_terminal};init.rb;1;0.42"
    handshake = "#{handshake.size.chr}#{handshake}"

    socket.write handshake
    @message = socket.read(3)

    puts "Message #{@message}"

    if (@message != "err" && @message)
      @message
    end
  end
end
