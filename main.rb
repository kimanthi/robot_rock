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
    class << self
      attr_accessor :apps
      @apps  = []
    end

    def self.attach
      Device::Display.clear
      Device::Display.print("Download App")
      puts "Connecting..."
      if Device::Network.connected? < 0
        if (ret = Device::Network.attach) == 0
          puts "Connected #{ret}"
        else
          puts "Attach fail #{ret}"
          return false
        end
      else
        puts "Already connected"
      end
      true
    end

    def self.update_app(file)
      # TODO Scalone: Refactor
      if self.attach
        puts "Donwloading #{file}..."
        ret = Device::Transaction::Download.request_file("#{file.split(".").first}.rb", file)
        Device::Network.walk_socket.close unless Device::Network.walk_socket.closed?

        check_error ret
      end
    end

    def self.params_dat
      if self.attach
        puts "Donwloading Params..."
        puts "#{ret = Device::Transaction::Download.request_param_file}"
        Device::Network.walk_socket.close unless Device::Network.walk_socket.closed?

        parse_apps if ret = check_error(ret)
        ret
      end
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

    def self.update_apps
      Device::Display.clear
      Device::Display.print("Press to Download #{@apps.size} apps", 3)
      getc
      @apps.each do |app|
        update_app(app[:rb])
      end
    end

    def self.menu
      Device::Display.clear
      Device::Display.print("Application Menu")
      selected = []

      apps.each_with_index do |app, i|
        if app[:available] == "1"
          selected << app
          Device::Display.print("#{app[:label]}", i+2)
        end
      end

      selected[getc.to_i - 1]
    end
  end
end

class CloudWalkInit
  def self.perform
    set_logical_number
    set_gprs_config
    params_dat
    update_apps
    execute(Main::Download.menu)
  end

  def self.set_logical_number
    number = Device::Setting.logical_number
    Device::Setting.logical_number = Main.form("Logical Number (#{number}): ", 0, 4, number, true)
  end

  def self.set_gprs_config
    # TODO Scalone We need  the same behaviour as numbers
    Device::Setting.apn  = Main.form("Apn  (#{Device::Setting.apn}): ", 0, 127, "", false)
    Device::Setting.user = Main.form("User (#{Device::Setting.user}): ", 0, 127, "", false)
    Device::Setting.pass = Main.form("Pass (#{Device::Setting.pass}): ", 0, 127, "", false)
  end

  def self.params_dat
    Device::Display.clear
    Device::Display.print("Press to Download Params", 3)
    getc
    Main::Download.params_dat
  end

  def self.update_apps
    Main::Download.update_apps
  end

  def self.execute(app)
    p app[:mrb]
    getc
    p require app[:mrb]
    p a = Device::Support.path_to_class(app[:mrb])
    a.call
    getc
  end
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

