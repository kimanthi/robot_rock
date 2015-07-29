
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

  def self.test_crypto
    Device::Display.clear
    puts "Clear Keys #{PAX::Crypto.delete_all_keys}"
    getc
    Device::Display.clear
    puts "Load IPEK #{PAX::Pinpad.load_ipek(1, PAX::Pinpad::LOADKEY_3DES, ["6AC292FAA1315B4D858AB3A3D7D5933A"].pack("H*"), ["FFFF9876543210E00000"].pack("H*"))}"
    getc
    Device::Display.clear
    puts "Enter pin ..."
    dukpt = PAX::Pinpad.get_pin_dukpt(1, "00004012345678909")

    dukpt.each do |k,v|
      Device::Display.clear
      puts "[#{k.inspect}]"
      puts "#{v.unpack("H*")}"
      getc(60000)
    end
    Device::Display.clear
    puts "Load PIN KEY #{PAX::Pinpad.load_pin_key(1, PAX::Pinpad::LOADKEY_DES, ["0123456789ABCDEF"].pack("H*"))}"
    getc
    Device::Display.clear
    puts "Enter pin ..."
    pin = PAX::Pinpad.get_pin(1, "00004012345678909")
    puts "#{pin.unpack("H*")}"
    puts "Finish"
    getc
  end

  def self.test_emv
    Device::Display.clear
    puts "Before"
    getc
    Device::Display.clear
    puts "Result #{PAX::EMV.core_init.inspect}"
    getc
  end

  def self.test_emv_get_parameter
    Device::Display.clear
    puts "Before"
    getc
    Device::Display.clear
    emv = PAX::EMV.get_parameter

    p "MerchId[" + emv["MerchId"] + "]"
    getc
    p "TermId[" + emv["TermId"] + "]"
    getc
    p "TerminalType[" + emv["TerminalType"].unpack("H*").first + "]"
    getc
    p "Capability[" + emv["Capability"].unpack("H*").first + "]"
    getc
    p "ExCapability[" + emv["ExCapability"].unpack("H*").first + "]"
    getc
    p "CountryCode[" + emv["CountryCode"].unpack("H*").first + "]"
    getc
    p "TransCurrCode[" + emv["TransCurrCode"].unpack("H*").first + "]"
    getc
    p "TransCurrExp[" + emv["TransCurrExp"].unpack("H*").first + "]"
    getc
    p "ReferCurrCode[" + emv["ReferCurrCode"].unpack("H*").first + "]"
    getc
    p "ReferCurrExp[" + emv["ReferCurrExp"].unpack("H*").first + "]"
    getc
    p "TransType[" + emv["TransType"].unpack("H*").first + "]"
    getc
    p "ForceOnline[" + emv["ForceOnline"].unpack("H*").first + "]"
    getc
    p "GetDataPIN[" + emv["GetDataPIN"].unpack("H*").first + "]"
    getc
    p "SurportPSESel[" + emv["SurportPSESel"].unpack("H*").first + "]"
    getc

    Device::Display.clear
    puts "END"

    getc
  end

  def self.test_icc
    self.test_emv
    Device::Display.clear
    puts "Before"
    getc
    Device::Display.clear
    PAX::EMV.init
    puts "after"
    getc
  end

  def self.test_icc_load_table
    @emv_hash = {
      :merchant_identifier=>"000000000000001",
      :merchant_category_code=>"0100",
      :terminal_identification=>"49000076",
      :terminal_type=>"22",
      :tdol=>"0000000000000000000000000000000000000000",
      :ddol=>"9F37049F47018F019F3201000000000000000000",
      :authorization_code_offline_approved=>"Y1",
      :authorization_code_offline_declined=>"Z1",
      :terminal_action_code_denial=>"0000000000",
      :terminal_action_code_online=>"0000000000",
      :terminal_floor_limit=>"0000C350",
      :reserved=>"00000000000000000000000000000000",
      :authorization_code_unable_online_offline_approved=>"Y3",
      :authorization_code_unable_online_offline_declined=>"Z3",
      :label=>"SMARTCON iEMV ON",
      :index=>"99",
      :length=>"284",
      :identification=>"1",
      :acquirer_id=>"04",
      :aid_length=>"07",
      :application_version_number_2=>"0084",
      :application_version_number_3=>"0000",
      :terminal_country_code=>"076",
      :transaction_currency_code=>"986",
      :aid=>"AAA00000010103000000000000000000",
      :application_type=>"01",
      :table_type=>"03",
      :application_version_number_1=>"008C",
      :terminal_capabilities=>"E0E8C0",
      :terminal_additional_capabilities=>"6000F0F000",
      :terminal_action_code_default=>"5000000000",
      :transaction_currency_exponent=>"2"
    }
    {:ca_public_key_exponent_byte_length=>"3", :ca_public_key_check_sum=>"4dddd1d9b9a3b2eeace63a5ba9dd6f4441ce10af00000000", :reserved=>"00", :acquirer_id=>"04", :ca_public_key_modulus_byte_length=>"176", :ca_public_key_modulus=>"D9E36579B94A5FF3150B64643D85C06E6E9F0682BE56CDD69FCB053913495BDBC327DA3CAC0EA2A0DA1D55DF7C66A0C6F6A9039FA72753C434F4A63BED54062799DF1F6D6E1F315A8F4109721126E11F4FF562C18A4AE6A4D9F0C2A5C2A8E44D6A98628C7E25290584F0F3D9ECE6566FDB7688596649BEC89A1CBC8BBED075538300D0D83FF8755E1CE73668908C387E14ACDF0F9F1DE436A5A07308812D6AE3A16170EDF2522B36FBE94358F50C0B69000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", :status_check_sum=>"1", :rid=>"AAA0000001", :ca_public_key_index=>"F1", :identification=>"2", :working_key=>"00000000000000000000000000000000", :index=>"08", :master_key_index=>"00", :length=>"611", :ca_public_key_exponent=>"010001"}
    # Smartcon iEMV - Online only
    #table_emv = "2841049907AAA0000001010300000000000000000001SMARTCON iEMV ON03008C008400000769862000000000000001010049000076E0E8C06000F0F000225000000000000000000000000000000000C3500000000000000000000000000000000000000000000000000000000000000000000000009F37049F47018F019F3201000000000000000000Y1Z1Y3Z3"
    # Smartcon iEMV - Offline
    #table_emv = "2841041007AAA0000001010400000000000000000001SMARTCON iEMV OF030001008400000769862000000000000001010049000076E0E8806000F0F001225000000000000000000000000000000000C3500000000000000000000000000000000000000000000000000000000000000000000000009F37049F47018F019F3201000000000000000000Y1Z1Y3Z3"
    #table_pki = "61120408AAA0000001F1003010001176D9E36579B94A5FF3150B64643D85C06E6E9F0682BE56CDD69FCB053913495BDBC327DA3CAC0EA2A0DA1D55DF7C66A0C6F6A9039FA72753C434F4A63BED54062799DF1F6D6E1F315A8F4109721126E11F4FF562C18A4AE6A4D9F0C2A5C2A8E44D6A98628C7E25290584F0F3D9ECE6566FDB7688596649BEC89A1CBC8BBED075538300D0D83FF8755E1CE73668908C387E14ACDF0F9F1DE436A5A07308812D6AE3A16170EDF2522B36FBE94358F50C0B6900000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000014dddd1d9b9a3b2eeace63a5ba9dd6f4441ce10af000000000000000000000000000000000000000000"
    # VISA
    table_emv = "2841040307A000000003101000000000000000000001CREDITO         03008C008400000769862000000000000001010049000076E0E8C06000F0F001220000000000000000000000000000000000C3500000000000000000000000000000000000000000000000000000000000000000000000009F37049F47018F019F3201000000000000000000Y1Z1Y3Z3"
    table_pki = "61120405A00000000399201030000128AB79FCC9520896967E776E64444E5DCDD6E13611874F3985722520425295EEA4BD0C2781DE7F31CD3D041F565F747306EED62954B17EDABA3A6C5B85A1DE1BEB9A34141AF38FCF8279C9DEA0D5A6710D08DB4124F041945587E20359BAB47B7575AD94262D4B25F264AF33DEDCF28E09615E937DE32EDC03C54445FE7E38277700000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000014ABFFD6B1C51212D05552E431C5B17007D2F5E6D000000000000000000000000000000000000000000"

    Device::Display.clear
    puts "CoreInit #{PAX::EMV.core_init.inspect}"
    getc
    puts "Init #{PAX::EMV.init}"
    getc
    row_emv = Device::EMVRow.new(table_emv)
    row_pki = Device::EMVRow.new(table_pki)
    general, app = PAX::EMV.parse_app(row_emv)
    pki = PAX::EMV.parse_pki(row_pki)

    puts "EMVParam #{PAX::EMV.set_parameter(general)}"
    #puts "APPDel #{PAX::EMV.del_apps}"
    puts "APPParam #{PAX::EMV.add_app(app)}"
    puts "PKIParam #{PAX::EMV.add_pki(pki)}"
    getc

    Device::Display.clear
    puts "Before smartcard"
    getc
    puts "Insert the Card"
    icc = PAX::EMV.icc
    timeout = Time.now + 30
    ret = nil
    loop do
      break if ((ret = icc.detected?) || timeout < Time.now)
    end

    Device::Display.clear
    puts "Detect #{ret}"
    getc
    puts "App Selection #{PAX::EMV.app_select(icc.slot, 1)}"
    getc

    Device::Display.clear
    puts "Read App Data #{PAX::EMV.read_data}"
    getc

    # E0:1110 0000|60:0110 0000
    # Terminal Capabilities Byte 1 - Card Data Input Capability
    # Manual key entry
    # Magnetic stripe
    # IC with contacts
    # RFU
    # RFU
    # RFU
    # RFU
    # RFU

    # D8:1101 1000|F8:1111 1000
    # Terminal Capabilities Byte 2 - CVM Capability
    # Plaintext PIN for ICC verification
    # Enciphered PIN for online verification
    # Signature (paper)
    # Enciphered PIN for offline verification
    # No CVM Required
    # RFU
    # RFU
    # RFU

    # C0:1100 0000|C8:1100 1000
    # Terminal Capabilities Byte 3 - Security Capability
    # SDA
    # DDA
    # Card capture
    # RFU
    # CDA
    # RFU
    # RFU
    # RFU

    Device::Display.clear
    puts "GetTlv 0x9F33" # E0E8C0
    puts "#{PAX::EMV.get_tlv(0x9F33).unpack("H*").to_s.upcase}"
    getc

    Device::Display.clear
    #   84:Dedicated File (DF) Name
    #   5A:Application Primary Account Number (PAN)
    # 5F34:Application Primary Account Number (PAN) Sequence Number (PSN)
    # 9F03:Amount, Other
    # 9F26:Application Cryptogram (AC)
    # 9F27:Cryptogram Information Data (CID)
    # 9F10:Issuer Application Data (IAD)
    # 9F37:Unpredictable Number (UN)
    # 9F36:Application Transaction Counter (ATC)
    #   95:Terminal Verification Results (TVR)
    #   9A:Transaction Date
    #   9C:Transaction Type
    # 9F02:Amount, Authorised
    # 5F2A:Transaction Currency Code
    #   82:Application Interchange Profile (AIP)
    # 9F1A:Terminal Country Code
    # 9F47:Integrated Circuit Card (ICC) Public Key Exponent
    # 9F35:Terminal Type

    # Amount, Authorised
    # puts "SetTlv 0x81 #{PAX::EMV.set_tlv(0x81, ["00000000"].pack("H*"))}"
    # Amount, Authorised
    puts "SetTlv 0x9F02 #{PAX::EMV.set_tlv(0x9F02, ["000000000123"].pack("H*"))}"
    # Amount, Other
    puts "SetTlv 0x9F03 #{PAX::EMV.set_tlv(0x9F03, ["000000000000"].pack("H*"))}"
    # Transaction Date
    puts "SetTlv 0x9A #{PAX::EMV.set_tlv(0x9A, ["120831"].pack("H*"))}"
    # Transaction Type
    puts "SetTlv 0x9C #{PAX::EMV.set_tlv(0x9C, ["00"].pack("H*"))}"
    # Application Usage Control
    puts "SetTlv 0x9F07 #{PAX::EMV.set_tlv(0x9F07, ["FFFF"].pack("H*"))}"
    # Terminal Floor Limit
    puts "SetTlv 0x9F1B #{PAX::EMV.set_tlv(0x9F1B, ["0000C350"].pack("H*"))}"
    # Terminal Type
    puts "SetTlv 0x9F35 #{PAX::EMV.set_tlv(0x9F35, ["23"].pack("H*"))}"
    # Unpredictable Number
    puts "SetTlv 0x9F37 #{PAX::EMV.set_tlv(0x9F37, ["0D5BD902"].pack("H*"))}"
    getc

    #05704230890341069
    #00004012345678909
    Device::Display.clear
    puts "GetTlv 0x57"
    puts "#{PAX::EMV.get_tlv(0x57).unpack("H*")}"
    puts "GetTlv 0x5F24"
    puts "#{PAX::EMV.get_tlv(0x5F24).unpack("H*")}"
    puts "GetTlv 0x5F28"
    puts "#{PAX::EMV.get_tlv(0x5F28).unpack("H*")}"
    getc

    Device::Display.clear
    puts "GetTlv 0x9F02"
    puts "#{PAX::EMV.get_tlv(0x9F02).unpack("H*")}"
    puts "GetTlv 0x9F03"
    puts "#{PAX::EMV.get_tlv(0x9F03).unpack("H*")}"
    puts "GetTlv 0x9F1B"
    puts "#{PAX::EMV.get_tlv(0x9F1B).unpack("H*")}"
    getc

    Device::Display.clear
    puts "Card Auth #{PAX::EMV.card_auth}"
    getc

    Device::Display.clear
    puts "Start Trans #{PAX::EMV.start_transaction(123)}"
    puts "GetTlv 0x9F27" #80
    puts "#{PAX::EMV.get_tlv(0x9F27).unpack("H*")}"
    getc

    # 02: 0000 0010                                                  10: 0001 0000
    # TVR Byte 1                                                     TVR Byte 2
    # Offline data authentication was not performed                  ICC and terminal have different application versions
    # SDA failed                                                     Expired application
    # ICC data missing                                               Application not yet effective
    # Card appears on terminal exception file                        Requested service not allowed for card product
    # DDA failed                                                     New card
    # CDA failed                                                     RFU
    # RFU                                                            RFU
    # RFU                                                            RFU

    # 04: 0000 0100                                                  00: 0000 0000
    # TVR Byte 3                                                     TVR Byte 4
    # Cardholder verification was not successful                     Transaction exceeds floor limit
    # Unrecognised CVM                                               Lower consecutive offline limit exceeded
    # PIN Try Limit exceeded                                         Upper consecutive offline limit exceeded
    # PIN entry required and PIN pad not present or not working      Transaction selected randomly for online processing
    # PIN entry required, PIN pad present, but PIN was not entered   Merchant forced transaction online
    # Online PIN entered                                             RFU
    # RFU                                                            RFU
    # RFU                                                            RFU

    # 00: 0000 0000
    # TVR Byte 5
    # Default TDOL used
    # Issuer authentication failed
    # Script processing failed before final GENERATE AC
    # Script processing failed after final GENERATE AC
    # RFU
    # RFU
    # RFU
    # RFU

    Device::Display.clear
    puts "GetTlv 0x95" # 0210040000
    puts "#{PAX::EMV.get_tlv(0x95).unpack("H*").to_s.upcase}"

    # E8: 1110 1000
    # TSI Byte 1
    # Offline data authentication was performed
    # Cardholder verification was performed
    # Card risk management was performed
    # Issuer authentication was performed
    # Terminal risk management was performed
    # Script processing was performed
    # RFU
    # RFU

    puts "GetTlv 0x9B" # E800
    puts "#{PAX::EMV.get_tlv(0x9B).unpack("H*").to_s.upcase}"
    getc

    Device::Display.clear
    puts "GetTlv 0x9F34" # 020300
    puts "#{PAX::EMV.get_tlv(0x9F34).unpack("H*").to_s.upcase}"
    getc
  end

  def self.emv_get_pki
    Device::Display.clear
    pki = PAX::EMV.get_pki(0)
    pki.each do |k,v|
      puts "[#{k.inspect}]-[#{v.inspect}]"
      getc(60000)
    end
    puts "Finish"
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
