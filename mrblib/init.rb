
module TestRobotRock
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

  def self.test_connect_wifi
    puts "Configure"
    Device::Setting.authentication = Network::Wifi::AUTH_WPA_WPA2_PSK
    Device::Setting.password       = "planobesemfio"
    Device::Setting.essid          = "PlanoBe"
    Device::Setting.channel        = 0
    Device::Setting.cipher         = 0
    Device::Setting.mode           = 0
    Device::Setting.media          = "wifi"
    puts "=" * 20
    puts "Attach #{Device::Network.attach}"
  end

  def self.test_socket
    puts "=" * 25
    puts "TCP #{(socket = TCPSocket.new('switch-staging.cloudwalk.io', 31415)).inspect}"
    socket
  end

  def self.test_handshake(socket, serial_terminal)
    handshake = "#{serial_terminal};init.rb;1;0.42"

    socket.write handshake.insert(0, handshake.size.chr)
    @message = socket.read(3)

    if (@message != "err" && @message)
      @message
    end
  end
end
