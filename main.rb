class Main < Device
  def self.call
    super
    Device::Display.clear
    Device::Display.print("CloudWalk", 1, 10)
    Device::Display.print("Serial #{Device::System.serial}", 3, 5)
    Device::Display.print("Press to Update", 5, 5)
    config
    getc
    Menu.perform
  end

  def self.config
    Device::Setting.logical_number = "1"
    Device::Setting.apn            = "zap.vivo.com.br"
    Device::Setting.user           = "vivo"
    Device::Setting.pass           = "vivo"
  end

  class Download
    def self.update(file)
      Device::Display.clear
      Device::Display.print("Download App")
      puts "Connecting..."
      if Device::Network.connected? < 0
        if (ret = Device::Network.attach) == 0
          puts "Connected #{ret}"
        else
          puts "Attach fail #{ret}"
        end
      else
        puts "Already connected"
      end

      # TODO Check attach
      puts "Donwloading App..."
      # TODO receive file app
      puts "#{ret = Device::Transaction::Download.request_file("app.rb", "app.mrb")} - #{getc}"
      Device::Network.walk_socket.close unless Device::Network.walk_socket.closed?

      puts "Donwloaded"
      getc

      check_error ret
    end

    def self.check_error(ret)
      case ret
      when 2
        puts "File is the same."
      when 1
        puts "Success."
      when 0
        puts "Encoding error."
      when -1
        puts "File not found."
      when -8
        puts "Serial number not found."
      else # when -7..-2
        puts "Communication fail."
      end

      getc
    end
  end
end

class Menu
  def self.perform
    execute(select_menu)
  end

  def self.select_menu
    Device::Display.clear
    Device::Display.print("Application Menu")
    Device::Display.print("1 - Execute", 2)
    Device::Display.print("2 - Update", 3)
    Device::Display.print("3 - Load", 4)
    Device::Display.print("4 - Remove", 5)
    getc
  end

  def self.execute(option)
    case option
    when "1"
      require "app.mrb" unless Object.const_defined?(:App)
      App.call
    when "2"
      Main::Download.update("app.mrb")
    when "3"
      load "app.mrb"
    when "4"
      File.delete("app.mrb")
    end
  end
end

