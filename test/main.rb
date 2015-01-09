require '../../out/robot_rock/da_funk.mrb'

class TestPlatform
  IO = ::IO

  class IO
    def get_string(min, max, mode)
      gets
    end
  end

  class Display
    def self.print(*args)
      puts args
    end

    def self.print_line(*args)
      puts args
    end

    def self.clear
    end
  end

  class Network
    def self.started?
      true
    end

    def self.connected?
      1
    end
  end

  class System
    def self.serial
      "50111541"
    end
  end

  def self.version
    "0.4.2"
  end
end

class Device
  self.adapter = TestPlatform
end

class Main < Device
  def self.call
    #Device::System.klass = Main
    Device::Setting.logical_number = "2"
    p Device::ParamsDat.update_apps
    p Miniz.unzip("white-surf-1.zip")
  end
end

Main.call
