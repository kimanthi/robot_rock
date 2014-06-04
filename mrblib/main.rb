

module Main
  def self.test_network_socket
    puts "=" * 20
    puts "Init #{Network.init(:gprs, apn: 'claro.com.br', user: 'claro.com.br', pass: 'claro.com.br')}"
    puts "Connect #{Network.connect}"
    iRet = 1
    while(iRet == 1)
      puts("Connected? #{iRet = Network.connected?}")
    end

    puts "=" * 25
    puts "Ping #{Network.ping("nas.scalone.com.br", 10000)}   "

    puts "=" * 25
    puts "TCP #{(tcp = TCPSocket.new('nas.scalone.com.br', 8000)).inspect}"
    puts "Send #{tcp.send('303132', 0)} "
    puts "Recv #{tcp.recv(10)} "
    puts "Closed? #{tcp.closed?}"
    puts "Close #{tcp.close} "
    puts "Closed? #{tcp.closed?}"
    puts "Disconnect #{Network.disconnect}"
  end

  def self.fib
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

  def self.test_gets
    puts "Start"
    Kernel.gets('4')
    puts "End"
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
    puts "asdfasdfasd"
    require 'test1.mrb'
    #require 'test2'
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

  def self.execute
    loop do
      begin
        test_require
      rescue => @exception
        puts "#{@exception.class}: #{@exception.message}\n#{@exception.backtrace.first}"
        IO.getc
        return nil
      end
    end
  end
end
