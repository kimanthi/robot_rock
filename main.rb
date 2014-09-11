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
  def self.form(txt, min=0, max=8, default="", is_number=true)
    Device::Display.clear
    puts txt
    if is_number
      form_number(default, min, max)
    else
      form_string(default, min, max)
    end
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

  def self.form_number(default, min, max)
    string = default
    loop do
      Device::Display.print(string, 2, 1)

      case (char = getc)
      when Device::IO::CANCEL
        return nil
      when Device::IO::ENTER
        return string if (string.size >= min)
      when Device::IO::BACK
        # TODO Check this code, for some reason string pointer get lost and print the entire string.
        # string = string[0..-2]
        string = "#{string[0..-2]}"
      else
        string << char if (string.size < max)
      end
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
      when 3
        puts "Serial number not found."
        return false
      when 2
        puts "File not found."
        return false
      when 1
        puts "File is the same."
      when 0
        puts "Success."
      when -1
        puts "Communication failure."
        return false
      when -2
        puts "Encoding error."
        return false
      when -3
        puts "IO Error."
        return false
      else
        puts "Communication fail."
        return false
      end

      true
    end

    def self.parse_apps
      @params = FileDb.new("params.dat") if File.exists?("params.dat")
      @apps   = []

      @params["apps_list"].gsub("\"", "").split(";").each do |app|
        values = app.split(",")
        mrb    = "#{values[1].gsub("#{Device::Setting.company_name}_", "").split(".")[0]}.mrb"
        @apps << {:label => values[0], :mrb => mrb, :file => values[1], :available => values[2], :crc => values[3]}
      end
      getc
    end

      getc
    end
  end
end

class Menu
  def self.perform(app)
    execute(select_menu, app)
  end

class DebugInit
  def self.perform
    config
    execute(menu, :App)
  end

  def self.config
    Device::Setting.logical_number = "1"
    Device::Setting.apn            = "zap.vivo.com.br"
    Device::Setting.user           = "vivo"
    Device::Setting.pass           = "vivo"
  end

  def self.menu
    Device::Display.clear
    Device::Display.print("Application Menu")
    Device::Display.print("1 - Execute", 2)
    Device::Display.print("2 - Update", 3)
    Device::Display.print("3 - Load", 4)
    Device::Display.print("4 - Remove", 5)
    Device::Display.print("5 - Params", 6)
    Device::Display.print("6 - TestWrite", 7)
    Device::Display.print("7 - Download Apps", 8)
    getc
  end

  def self.execute(option, app)
    path     = "#{app.to_s.downcase}.mrb"
    case option
    when "1"
      require(path)
      Device::Support.path_to_class(path).call
      getc
    when "2"
      Main::Download.update_app(path)
    when "3"
      puts "Load #{load(path)}"
      getc
    when "4"
      puts "Delete #{File.delete(path)}"
      getc
    when "5"
      Main::Download.params_dat
      getc
    when "6"
      puts "form: #{Main.form("Logical Number: ", 0, 4, "1234", false)}"
      getc
    when "7"
      Main::Download.update_apps
      getc
    end
  end
end

