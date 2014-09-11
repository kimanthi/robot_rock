class Main < Device
  APP = :App

  def self.call
    super
    Device::Display.clear
    Device::Display.print("CloudWalk", 1, 10)
    Device::Display.print("Serial #{Device::System.serial}", 3, 5)
    Device::Display.print("Press to Update", 5, 5)
    config
    getc
    Menu.perform(APP)
  end

  def self.config
    Device::Setting.logical_number = "1"
    Device::Setting.apn            = "zap.vivo.com.br"
    Device::Setting.user           = "vivo"
    Device::Setting.pass           = "vivo"
  def self.form_string(default, min, max)
    puts "\n"
    string = Device::IO.get_string(min, max)
    return default if string.empty?
    string
  end

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
      puts "#{ret = Device::Transaction::Download.request_file("#{file.split(".").first}.rb", file)} - #{getc}"
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
  def self.perform(app)
    execute(select_menu, app)
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

  def self.execute(option, app)
    path = "#{app.to_s.downcase}.mrb"
    case option
    when "1"
      require path unless Object.const_defined?(app)
      App.call
    when "2"
      Main::Download.update(path)
    when "3"
      load path
    when "4"
      File.delete(path)
    end
  end
end
