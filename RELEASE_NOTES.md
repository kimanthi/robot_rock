# RobotRock

RobotRock is the Ruby Walk Framework for PAX.

## Contact

If you have any problem, please get in touch with us by the [e-mail - support@cloudwalk.io](mailto:support@cloudwalk.io) or ZenDesk.
Documentation could be found on the [here](https://dl.dropboxusercontent.com/u/10674904/ruby/doc/frames.html#!_index.html).

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

