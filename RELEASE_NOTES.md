# RobotRock

RobotRock is the Ruby Walk Framework for PAX.

## Contact

If you have any problem, please get in touch with us by the [e-mail - support@cloudwalk.io](mailto:support@cloudwalk.io) or ZenDesk.
Documentation could be found on the [here](https://dl.dropboxusercontent.com/u/10674904/ruby/doc/frames.html#!_index.html).

### 5.23.0 - 2017-10-10

- Update main (1.31.0)
    - Update funky-emv (0.11.0)
        - Implement Row#accurate_aid to support length check.
        - Fix aid row comparison checking length on all situations.

### 5.22.0 - 2017-09-27

- Update Gemfile.lock to update main gems.

### 5.21.0 - 2017-09-26

- Update mruby-pax
    - Add aid content to application selection.
- Update main (1.30.0)
    - Update funky-emv (0.10.0)
        - Check emv_application_name_table for application label display.
    - Update da_funk (0.19.0)
        - Update guide.

### 5.20.0 - 2017-09-15

- Update main (1.29.0)
    - Add MIT License to README.
    - Fix display font setup.
- Update mruby-pax
    - Refactoring Audio API.
    - Apply 22 columns to s920.
    - Configure terminal to not interrupt print if any problem.
    - Refactoring Printer sizes
    - Fix filename paratemer at font Printer API.
    - Add configuration of gray level, space and indent for printer.
    - Configure printer to no pre-feeding paper.
- Udpate da_funk (0.19.0)
    - Update README_GUIDE.

### 5.19.0 - 2017-09-08

- Update main (1.28.0)
    - Bug Fix check if font file exist to update it.

### 5.18.0 - 2017-09-06

- Update main (1.27.0)
    - Add Flags section at README.
    - Update funky-emv (0.9.1).
        - Add sleep time after application name display.
        - Check params dat flag emv_application_name_table to show application name from table.

### 5.17.0 - 2017-09-06

- Update da_funk (0.16.0)
    - Implement custom print at attach helper.

### 5.16.0 - 2017-09-05

- Implement custom print at attach helper.
- Create interface for font customization.
- Update main (1.24.0)
    - Bug fix logical number form at initialisation flow.
    - Support to custom font.
    - Update posxml_parser (0.23.0).
        - Move EventListener to main application.

### 5.15.0 - 2017-08-30

- Update main (1.22.0)
    - Move cloudwalk.rb to cloudwalk_setup.rb.
    - Add cloudwalk gem.
- Update main (1.23.0)
    - Adopt cloudwlak 0.7.1.
    - Update da_funk (0.15.0).
        - Add task to setup(initialize) Network based in the current configuration.
        - Reload Network, Setting and ParamsDat after app execution.

### 5.14.0 - 2017-08-21

- Update main (1.21.0)
    - Check if handshake was performed to display successful message on Paymentchannel reconnect.
    - Add timeout read loop to payment channel handshake.
    - Update posxml_parser (0.22.0).
        - Fix posxml_socket_read size buffer request.

### 5.13.0 - 2017-08-18

- mruby-pax
    - Improve version control management.

### 5.12.0 - 2017-08-18

- Update main (1.20.0).
    - Fix ParamsDat loading when download it.

### 5.11.0 - 2017-08-16

- Update main (1.19.0).
    - posxml_parser (0.20.1)
        - Implement image loop display for tcp receive operations.
        - Decrease network_receive getc timeout from 300 to 200 mili.
        - Clean tcp_image_loop after use.

### 5.10.0 - 2017-08-16

- Update main (1.18.0).
    - Support disable_datetime flag.
- Update da_funk (0.13.0).
    - Implement tcp_recv_timeout as custom attribute at Device::Setting.
- Update mruby-pax.
    - Increase DNS timeout from 5000 to 30000 milliseconds.

### 5.9.0 - 2017-08-10

- Update mruby-pax
- da_funk (0.11.0)
    - Fix connection_management flag.
- main (1.16.0)
    - Decrease getc wait milliseconds of key_main handler from 700 to 200.
    - Bug fix, only close PaymentChannel client if it was created.
    - Rescue SocketError at PaymentChannel.
    - Fix connection management flag.
    - Update cloudwalk_handshake (0.10.0)
        - Log SSL exceptions.
    - funky-emv (0.8.0)
        - Support to ICC_CMD_ERR on EmvPax.
        - Remove application version debug.
        - Change Funky-EMV license.
    - posxml_parser (0.17.0)
        - Remove ISO20022 debugs

### 5.8.0 - 2017-08-08

- Update mruby-pax
    - Support to send size on Serial#read.
    - Implement _getc_read and temporarily adopt GetMainKey (no IO close) in getc, instead of GetKey (close IO).
- Update mruby-pax-network
    - Define a size to read geolocation information and avoid timeout.
- Update main (1.15.0)
    - Adopt print_last for PaymentChannel displays.
    - Check if Device is connected on PaymentChannel life check.
    - Refactoring primary_communication label return on PaymentChannel.
    - Bug fix set media_primary on media configuration.
    - Check if is main connection is running to validate fallback at ConnectionManagement.
    - Additional check to ConnectionManagement before try primary connection recovery.
    - Adopt Device::Network.shutdown at payment channel handlers and trigger fallback recovery if primary communication try has failed.
    - Adopt print_last at CloudWalk and MediaConfiguration.
    - Update cloudwalk_handshake (0.9.0)
        - Add rescue for SSL exceptions.
        - Add cloudwalk gem.
    - da_funk (0.10.0)
        - Define pt-br as default locale.
        - Implement Kernel#print_last.
        - Adopt print_last for Herlper#attach.
        - Implement Device::Network.shutdown, what call disconnect and power(0).
        - Update cloudwalk_handshake (0.9.0), funky-emv (0.9.0) and posxml_parser(0.16.0).
    - posxml_parser (0.16.0)
        - Add cloudwalk gem.
        - Add ISO20022 initial implementation.
        - Add 3 instructions related with ISO 20022:
            - iso20022_new(document).
            - iso20022_add(tag, value).
            - iso20022_build(variablereturn, buffer).

### 5.7.0 - 2017-08-03

- Update main (1.13.0)
    - Fix exception when connection management fallback not available.

### 5.6.0 - 2017-08-02

- Update mruby-pax
    - Fix CA Public Key Moddules Byte Length conversation for unexpected value.
- Update main (1.12.0)
    - Update funky-emv (0.7.0)
        - Get AID from table row on SharedLibrary during the init.
        - Get tag 9F06 to set AID when EMVShared library.
        - Get tag 9F06 to set AID when EMVPax.
        - Send aid from 9f06 if isn’t necessary to delete tag too.
        - Remove EmvSharedLibrary.go_on_chip_tlv_result debugs.
        - Fix EmvPax.get_aid_tlv getting the correct tags (4F and 9F12).

### 5.5.0 - 2017-07-25

- Update main (1.11.0)
    - Update da_funk(0.9.3)
        - Refactoring Network.configured? fixing the return which must be a bool.
        - Create Device::Setting.wifi_password and Device::Setting.apn_password.
    - Adopt da_funk 0.9.3: - Device::Setting.wifi_password; - Device::Setting.media_primary; - Bool return for Device::Network.connected?
    - Refactoring Connection Management and Payment Channel handlers to support fallback communication.
    - Update posxml_parser(0.15.3)
        - Adopt da_funk 0.9.3: - Device::Setting.wifi_password; - Bool return for Device::Network.connected?
        - Black variablereturn if mcc information nil at system_info.
        - Remove windows clear at input_integer.
        - Refactoring payment channel use to better debug.
    - Update funky-emv(0.6.0)
        - Fix finish tags generation.

### 5.4.5 - 2017-07-13

- Update main (1.10.0)
    - Update funky-emv (0.5.9)
        - Remove extra “F” when get tag 5A(PAN).

### 5.4.4 - 2017-07-13

- Update main (1.9.0)
    - Add all files from resources to keep in format process.

### 5.4.3 - 2017-07-12

- Update main (1.8.0)
    - Do not exclude cw_apns.dat.
    - Update da_funk (0.9.1)
        - Fix file deletable check and extra parameters for additional files at ParamsDat.format!.
    - Update posxml_parser (0.15.2)
        - Raise InstructionNotFoundError during XsdParser#to_bytecode if instruction not found in xsd.
        - Fix PosxmlCompiler parser to avoid empty statements.
        - Add warning for application size limit.
        - Update da_funk (0.9.1).
        - Update funky-tlv(0.2.3).
    - Update funky-tlv (0.2.3)
        - Refactoring Hash.from_ber_tlv replacing while for loop do, and add a test case.
        - Add option -b to compilation using cloudwalk CLI.

### 5.4.2 - 2017-07-05

- Update mruby-pax.
- Update main(1.7.0).
- Update da_funk(0.9.0).

### 5.4.1 - 2017-07-04

- Update mruby-pax.
- Update mruby-pax-network.

### 5.4.0 - 2017-06-30

- Update main(1.6.0).
- Update da_funk(0.8.6).
- Update mruby-pax.

### 5.3.5 - 2017-06-22

- Update main(1.5.0).
- Update da_funk(0.8.5).

### 5.3.4 - 2017-06-20

- Update main(1.4.9).
- Update mruby-pax-network.

### 5.3.3 - 2017-06-13

- Support to receive long press keyboard entry.
- Update da_funk(0.8.4), main(1.4.8), mruby-pax and mruby-pax-network.

### 5.3.2 - 2017-06-01

- Update main (1.4.7).
- Update mruby-pax.

### 5.3.1 - 2017-05-15

- Update main (1.4.4).

### 5.3.0 - 2017-05-15

- Update main (1.4.3).
- Update mruby-pax.
- Update mruby-poalarssl.
- Update da_funk (0.8.2).
- Support to configure Context based in SIGNATURE flag.

### 5.2.0 - 2017-04-05

- Update main (1.4.2).
- Update mruby-pax.

### 5.1.2 - 2017-03-30

- Update main (1.4.1).
- Update da_funk (0.8.1).

### 5.1.1 - 2017-02-03

- Update main (1.3.3).
- Update da_funk(0.8.0).
- Update mruby-pax.

### 5.1.0 - 2017-01-19

- Update main (1.3.2).
- Stable version.

### 5.0.11 - 2017-01-17

- Update main (1.3.1).
- Update mruby-pax.

### 5.0.10 - 2017-01-04

- Update main (1.2.6).
- Update mruby-pax.

### 5.0.9 - 2017-01-02

- Update main (1.2.5).
- Update mruby-pax.

### 5.0.8 - 2016-12-27

- Update mruby.
- Update main (1.2.3).
- Update mruby-miniz(1.0.0).
- Update mruby-context (1.3.0)
- Update PAX (1.4.0).
- Update da_funk (0.7.18).

### 5.0.6 - 2016-11-03

- main (1.1.6)

### 5.0.5 - 2016-10-28
- mruby-pax (1.3.1)
  - Fixed Magnetic.tracks returns, sometimes it was returning empty.

### 5.0.4 - 2016-10-11

- da_funk(0.7.12)
  - Bug fix Crypto class check.
  - Remove commented code at struct.rb.
  - Bug fix replace Device::Setting.sim_pim by sim_pin.
- main (1.1.4)

### 5.0.3 - 2016-10-10

- funky-emv (0.4.2)

### 5.0.2 - 2016-10-06

- Implement task to generate device.sig.
- Fix custom crash function.
- da_funk (0.7.10)
  - Refactoring Helper.menu supporting custom forward and back key, and bug fix pagination.
  - Support custom forward and back keys.
- funky-emv (0.4.1)
  - Displat tag 0x50 if tag 9F12 is empty at selection.
  - Bug fix return unless scheme fond in EmvRow parse.
  - Bug fix create hash before check tlv in finish.
- mruby-pax (1.3.0)
  - Implement custom back and forward keys.
  - define default values for scripts variables.
  - Add PAX::EMV.param_flag.
  - Bug fix properly send cashback in EMVStartTrans.
  - Refactoring SetMCKParam to get params before set.
  - Remove function logContext, replaced by ContextLog.
  - Touch.c
  - Rename ContextLog.error by ContextLog.exception
  - Implement Touch bind.
  - Only open MSR once.
  - Remove display at Emv.del_pkis.
  - Refactoring cEMVWaitAppSel to send a unique hash instead of hash and arrya(labels) to callback.
  - Bug fix, check if cash back is 0 to send NULL and avoid Application Usage Control processing problems.
  - Always set ucBypassPin 0 and ucBatchCapture 1.
  - Review table parameters values and sizes at emv.c
  - Perform PKI check sum calculation if statu_check_sum is 0.
  - Review all commentaries and values at emv.rb.
  - Store pkis in Emv.pkis instead of load in initialisation time, and let to dynamically load it in transaction time.
  - Implement EMV.random.
  - Refactoring returns and commentaries at src/emv.c.
  - Add logContext function to call ContextLog.info in C.
  - Fix rss object consumption in Pinpad operations.
  - Refactoring OsPedSetAsteriskLayout call to wait input in the right line.
  - Add EMV.del_pkis.
  - Return EMV_OK in cEMVSetParam and cEMVSM3.
  - Add function to log emv errors.
  - Refactoring pki parse calculating pki check sum.

### 5.0.1 - 2016-10-03

- da_funk (0.7.9)
  - Implement seconds to Scheduler timer.
  - Implement Device::IO.getxy to support touchscreen.
  - Adopt try_user in Device::Network.
  - Implement Helper#try_user to implement a user interruption.
  - Use getc(milliseconds) instead of sleep to improve UX in Helper.
  - Replace ContextLog.error by ContextLog.exception.
  - Adopt DaFunk::Struct instead of Struct in Notifications.
  - Send a Serf#event if creation interval exceed.
  - Fix leak I18n copying translation in every call.
  - Close serf socket if command has no reply.
  - Implement DaFunk::Struct to avoid memory leaks from mruby.
  - Check key cancel and return it at get_format.
  - Update README.
- main (1.1.1)
  - Bug fix timer handler call.
  - Refactoring admin menu improving UX and translation.
  - EMV Listener only call initialise if icc.detected.
  - Enable Notifications
  - Display emv password in the next line.
- funky-emv (0.4.0)
  - Fix script processing sending to TLV command only what EMVCompleteTrans require.
  - Change POS Entry for 0x04.
  - Display clear after get_pin functions.
  - Replace 0x9C(Transaction Type) from EMV_PAYMENT(0x40) EMV_GOODS&EMV_CASH (0x00)
  - Implement InitData.localtion_mode.
  - Add EmvTransaction.to_json/from_json methods to serialise and deserialise data and info structures.
  - Add refund to process_data.
  - Delete and load pki’s keys on every transaction.
  - Set tlv 0x8A from self.finish_data.auth_resp_code at EmvPax.finish
  - Remove ICC Application Usage Control definition.
  - Do not generate tags map in load time, but pre define in ruby to improve performance.
  - Refactoring lines and row to display application label.
  - Add EmvRow#string
  - Support to start EmvStruct with pre defined values.
  - Bug fix doesn’t call set_tlv for amount_other if the value is 0.
  - Refactoring all returns at EmvPax to use values from biblioteca compartilhada.
  - Return PPCOMP_TABERR if problem to load any table row.
  - Review timeouts and commentaries at pin block callbacks.
  - Refactoring selection block using menu function from helper and return values from constants of PAX::EMV.
  - Delete pkis before read tables.
  - Use random to generate Unpredictable Number.
  - Indent emv_pax.rb.
  - Review get_pin_block clear and message display.
  - Clear display after print :emv_not_accept.
  - Add 200 milliseconds sleep time before call any get pin function to fix display problems.
  - Replace application label tag from 0x50 to 0x9F12.
- posxml_parser (0.9.3)
  - Replace schedule minutes for seconds.
  - Support INIT_DATA[:bAcquirerLocationMode].
  - input_money returns -2 if Device::IO::CANCEL.
  - Do not start a new runtime in EventHandlers.
  - Refactoring card_read changing check order.
  - Replace ContextLog.error by ContextLog.exception.
  - Return empty value at input_money if user cancel.
  - Add bfRefund/refund from PROCESS_DATA.
  - Support json intilization parameter at runtime level.
  - Comment ContextLog.info calls.
  - Add funky-emv version in gem spec.
- Add Custom crash report.

### 5.0.0 - 2016-09-06

- Update mruby-dir, mruby-hmac, mruby-json, mruby-pack, mruby-regexp-pcre, mruby-socket, mruby-tempfile, mruby-tinyxml2.
- Update da_funk(0.7.5), main(1.1.0), sdk, mruby-context(1.0.0) and mruby-pax(1.2.0) to support all emv flows.
- Replace masamitsu-murase/mruby-hs-regexp for scalone.
- Implement memory profiling.
- Support to s920.

### 0.6.8 - 2015-04-18 - Update sobmodules

- Update main version to 1.0.8.
- Update mruby-polarssl supporting DES instructions.
- Update DaFunk version to 0.7.3.

### 0.6.7 - 2015-03-14 - Update main version to 1.0.7

- Update main version to 1.0.7.

### 0.6.6 - 2015-03-14 - Update main, mruby-pax and da_funk

- Update da_funk(0.7.0), main(1.0.6), mruby-pax(1.0.1) and mruby-pax-network(1.1.0).
- Add link to libxui.so on out/lib/.

### 0.6.5 - 2015-02-18 - Update main(1.0.4) and da_funk(0.6.6) version

- Update da_funk(0.6.7), main(1.0.5), sdk(2.8.0), mruby-pax(1.0.0) and mruby-pax-network(1.0.0).
- Remove png's from res.
- Remove Status Bar responsibility.

### 0.6.4 - 2015-02-18 - Update main(1.0.4) and da_funk(0.6.6) version

- Internal: Add mrbc task to mrb_load task.
- Update main(1.0.4) and da_funk(0.6.6) version.

### 0.6.3 - 2015-02-15 - First stable version

- First stable version.

### 0.4.3 - 2014-10-24 - Communication support

- Add GPSRS support.
- Add DaFunk Support.
- Add SDK 2010.

### 0.4.2 - 2014-09-05 - First Version

- First Version.
