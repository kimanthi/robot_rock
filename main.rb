class Main < Device
  def self.call
    super

    Device::Display.clear
    Device::Display.print("CloudWalk", 1, 5)
    Device::Display.print("Serial #{Device::System.serial}", 2, 4)

    Device::Display.print(" 1 - CloudWalkInit", 5)

    if getc == "1"
      CloudWalkInit.perform
    end

    getc
  end
end

class CloudWalkInit
  include Device::Helper

  def self.perform
    self.set_logical_number
    self.set_wifi_config
    if Device::ParamsDat.update_apps
      self.execute(Device::ParamsDat.application_menu)
    end
  end

  def self.set_logical_number
    number = Device::Setting.logical_number
    Device::Setting.logical_number = form("Logical Number (#{number}): ", 0, 4, number, true)
  end

  def self.config
    Device::Display.clear
    puts "Would like to configure connection?"
    puts "1 - Yes"
    puts "2 - No"
    configure = getc
    if (configure == "1")
      # TODO Scalone check media
      Device::Setting.media = Device::Network::MEDIA_WIFI
      Device::Setting.authentication = form(" Authentication (#{Device::Setting.authentication}): ", 0, 127, "", false)
      Device::Setting.password       = form(" Password (#{Device::Setting.password}): ", 0, 127, "", false)
      Device::Setting.essid          = form(" Essid (#{Device::Setting.essid}): ", 0, 127, "", false)
      Device::Setting.channel        = form(" Channel (#{Device::Setting.channel}): ", 0, 127, "", false)
      Device::Setting.cipher         = form(" Cipher (#{Device::Setting.cipher}): ", 0, 127, "", false)
      Device::Setting.mode           = form(" Mode (#{Device::Setting.mode}): ", 0, 127, "", false)
    end
  end

  def self.set_wifi_config
    #WIFI
    Device::Setting.media          = Device::Network::MEDIA_WIFI
    Device::Setting.mode           = Device::Network::MODE_STATION

    #Device::Setting.authentication = Device::Network::AUTH_WPA_WPA2_PSK
    #Device::Setting.cipher         = Device::Network::PARE_CIPHERS_CCMP
    #Device::Setting.password       = "desgracapelada"
    #Device::Setting.essid          = "Barril do Chaves"
    #Device::Setting.channel        = "0"

    # WIFI Office
    Device::Setting.authentication = Device::Network::AUTH_WPA_WPA2_PSK
    Device::Setting.cipher         = Device::Network::PARE_CIPHERS_TKIP
    Device::Setting.password       = "planobesemfio"
    Device::Setting.essid          = "PlanoBe"
    Device::Setting.channel        = "0"

    #GPRS
    #Device::Setting.mode           = Network::MEDIA_GPRS
    #Device::Setting.logical_number = "1"
    #Device::Setting.apn            = "zap.vivo.com.br"
    #Device::Setting.user           = "vivo"
    #Device::Setting.pass           = "vivo"
  end


  def self.set_gprs_config
    # TODO Scalone We need  the same behaviour as numbers
    Device::Setting.apn  = form("Apn  (#{Device::Setting.apn}): ", 0, 127, "", false)
    Device::Setting.user = form("User (#{Device::Setting.user}): ", 0, 127, "", false)
    Device::Setting.pass = form("Pass (#{Device::Setting.pass}): ", 0, 127, "", false)
  end
end

