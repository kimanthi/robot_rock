# RobotRock

RobotRock is the Ruby Walk Framework for PAX.

## Contact

If you have any problem, please get in touch with us by the [e-mail - support@cloudwalk.io](mailto:support@cloudwalk.io) or ZenDesk.
Documentation could be found on the [here](https://dl.dropboxusercontent.com/u/10674904/ruby/doc/frames.html#!_index.html).

### 7.18.0 - 2020-11-16

- Update main
  - Added new icon for 3G connection;
  - Added new s920 main screen image;
  - Added support to touchscreen events which executes other apps;
  - Added support to send additional parameters in the function executed from scheduler;
  - Update da_funk (3.30.0).
- Update da_funk (3.30.0)
  - Added new method main_image_format on Device::Display;
  - Use main_image_format method to get the image name instead adapter;
  - Added new class DaFunk::Transaction::Reversal.

### 7.17.0 - 2020-11-04

- Update main (3.60.2)
  - Update cloudwalk_handshake (1.21.3)
    - Merge all headers sent by the payment application.
  - Update da_funk (3.29.1)
- Update da_funk (3.29.0)
  - Added support to Ruby SecureRandom;
  - Update cloudwalk_handshake (1.21.3).
- Update da_funk (3.29.1)
  - Fix battery charging status. When power supply is connected the SDK always returns 50% of battery, in this case it won't show the percentage until the SDK returns 100%.

### 7.16.5 - 2020-10-26

- Update main (3.60.1)
  - Added device was restarted info on log.

### 7.16.4 - 2020-10-07

- Update main (3.60.0)
  - Update da_funk (3.28.2);
  - Update some images;
  - Added new handler to check params.dat status each 60 minutes;
  - Update cloudwalk_handshake (1.21.1)
    - Changed method name infinitepay? to http? on log register;
    - Use transaction_http_enabled flag from params.dat to identify http transactions.
- Update da_funk (3.28.2)
  - Added support of params.dat file restore if it was corrupted;
  - Wait 3 seconds before restart after main update;
  - Fixed method_missing exception.

### 7.16.3 - 2020-09-30

- Update main (3.59.3)
  - Concatenate and send all logs at once;
  - Fixed filename. Log txt should have the date of the day that is being sent;
  - Do not send full path as LogsMenu#send_file is already adding path;
  - Send all log files separated;
  - Moved logs ui feedback to LogsMenu#send_file_menu and LogControl#upload;
  - LogsMenu#send_file return booleam as result;
  - Store return of each log send.

### 7.16.2 - 2020-09-29

- Update main (3.59.2)
  - Update cloudwalk_handshake (1.21.0)
    - Added log for ssl handshake;
    - Fixed CwHttpSocket#connected? method;
    - Make sure to close socket if exeception is raised;
    - Added CwHttpSocket#closed? method;
    - Check if CwHttpSocket#response is a valid response before parse;
    - Only write on socket if socket is alive;
    - Return communication error if ssl error or socket closed;
    - Fixed json body on communication error response.

### 7.16.1 - 2020-09-26

- Update da_funk (3.28.1)
  - Close socket in case of ssl exceptions;
  - Do not assign nil to PaymentChannel#current and client on error because this is already being done on PaymentChannel#close.
- Update main (3.59.1)
  - Do not try to download system parts if update file does not exists;
  - Check if update dat object exists on SystemUpdate#done? before start it;
  - Update da_funk (3.28.1).

### 7.16.0 - 2020-09-25

- Update main (3.59.0)
  - Add main application version on config.dat file;
  - Moved thread loop process to Main#thread_loop metohod, also added rescue on Main#thread_loop;
  - Update cloudwalk_handshake (1.20.1);
    - Fixed TypeError String exception, sometimes request does not include a body;
  - Update da_funk (3.27.0);
  - Improved system update messages;
  - Show system update message at line 0 and alway clear it before;
  - Added system_update_start message;
  - Check system update status at zero position of string array;
  - Print system update message after device restart, in case system update is in progress;
  - Added additional information in the system update file in order to know that the device needs to restart before proceed with the system update;
  - Added CloudwalkUpdate#wait_connection method;
  - Added CloudwalkUpdate#count_down method;
  - Added CloudwalkUpdate#system_in_progress? method;
  - Wait terminal to connect before start system update in case device has restarted;
  - Added system update management file on CloudwalkUpdate;
  - Fixed display messages on application update proccess;
  - Update da_funk (3.28.0).
- Update da_funk (3.27.0)
  - Print bitmap if exists on DaFunk::ParamsDat#restart;
  - Add main application version on config.dat file.
- Update da_funk (3.28.0)
  - Check if system update file is present after device restart in order to continue with system update process;
  - Implemented block to write and break line if message has '\n'.

### 7.15.0 - 2020-09-14

- Update main (3.58.0)
  - Update cloudwalk_handshake (1.20.0)
    - Added CwHttpSocket#to_acquirer_payload method, this method is responsible for returning a common payload for all requests when the requester is the infinitepay payment application;
  - Update da_funk (3.26.0);
  - Update virtual keyboard images.
- Update da_funk (3.26.0)
  - Fixed error on virtual keyboard, chars y and Y were duplicated;
  - Update cloudwalk_handshake (1.20.0).

### 7.14.0 - 2020-08-28

- Update da_funk (3.25.1)
  - Set DaFunk::Helper::StatusBar#connected as false on system update process so it will be cached again.
- Update main (3.57.0)
  - Update da_funk (3.25.1);
  - Call to CloudwalkUpdate#system instead of SystemUpdate#start so the user can cancel the update process if he wants;
  - Added new parameter system_update_main_enabled to enable system update with UI;
  - Added system_update_interval scheduler on communication thread in order to download all pieces in background;
  - Added system_update_thread_enable parameter to enable/disable update with thread;
  - Turn backlight on in the update process;
  - Delete system_update file if user cancel update process;
  - Start connection on input amount to make contactless transactions a bit faster;
  - Added SystemUpdate#done? method in order to check if all pieces were downloaded and to add system_update file again if user has canceled it before.

### 7.13.2 - 2020-08-25

- Update main (3.55.0)
  - Do not perform default gprs config if network_configured is 1;
  - Added images to be used on log send process;
  - Added support to send logs from another app call;
  - Only try to send log if socket is connected, also display images to show operation result.
  - Convert sim_id to String before access characters;
  - Only save media on config.dat file if sim_id is not nil;
- Update main (3.56.0)
  - Added InputTransactionAmount#contactless_minimum_amount_permited;
  - Added InputTransactionAmount#contactless_amount_under_permited;
  - Display amount bitmap inside amount loop;
  - Added InputTransactionAmount#amount_under_minimum_not_permitted;
  - Show amount under minimum permitted message on screen;
  - Fixed i18n message symbol;
  - Added new i18n text message;

### 7.13.1 - 2020-08-21

- Update mruby-emv.

### 7.13.0 - 2020-08-18

- Update da_funk (3.25.0)
  - Added switch_http_enabled setting;
  - Removed infinitepay_authorizer and infinitepay_api settings.
- Update main (3.54.0)
  - Change thread execution and status bar check order, Necessary to not free CPU processing time on transaction execution;
  - Added CloudwalkSetup#resume_update;
  - Moved CloudwalkSetup#resume_update to AdminConfiguration#configure;
  - Implemented AdminConfiguration#device_activated?;
  - Perform device configs in case device is not activated;
  - Rename method AdminConfiguration#configure to AdminConfiguration#configure_payment_application;
  - Update cloudwalk_handshake (1.19.0);
    - Removed methods:
      - CwInfinitePayHostSetting#api?;
      - CwInfinitePayHostSetting#api_allowed_appication?;
      - CwInfinitePayHostSetting#authorizer_allowed_appication?;
      - CwInfinitePayHostSetting#authorizer?;
      - CwInfinitePayHostSetting#google_endpoint?;
    - Removed authorizer urls constants;
    - Added CwInfinitePayHostSetting#v2_protocol? method;
    - Convert infinitepay_url parameter to string and check empty;
    - Added CwInfinitePayHostSetting#switch_http_enabled?;
    - Return switch http url if it's enabled otherwise return infinitepay url;
    - Add headers based on switch http config or acquirer app;
    - Encode request based on protocol being used (v1/v2);
    - Use safe navigation on CwHttpSocker.code;
    - Log possible exception on CwHttpSocket.read;
    - CwHttpSocket Persist request.code right after response that avoids thread execution window and we are able to reduce 1 second;
    - Added transaction_accept_encoding parameter support.
    - Update da_funk (3.25.0).
- Update mruby-context
  - Add some extra check before deal with sem thread channel. Check maximum size (possible leak if happen) and check if it’s blocked and return right way, don’t insist.
  - Change the way of check if thread control is valid
- Update mruby-pax-network
  - Increase connection check window to 10 seconds;
  - Check if there’s a socket open to check connection.

### 7.12.0 - 2020-08-11

- Update da_funk (3.24.4)
  - Add defensive code to gsub calls.
- Update main (3.53.0)
  - MediaConfiguration defensive code with gsub;
  - Update da_funk (3.24.4).
- Update mruby-context
  - Invert LOAD_PATH to always search dependencies on main application in case app is not present.

### 7.11.0 - 2020-08-01

- Update da_funk (3.24.2)
  - Do not remove company name to file path when ruby app.
- Update main (3.51.0)
  - Update da_funk (3.24.2).
- Update da_funk (3.24.3)
  - Fixed path name on DaFunk::Application.
- Update main (3.52.0)
  - Update da_funk (3.24.3).

### 7.10.2 - 2020-07-30

- Update appinfo version (Forgot to do that in the last version)

### 7.10.1 - 2020-07-29

- Update da_funk (3.24.1)
  - Infinitepay authorizer setting 1 as default.
- Update main (3.50.0)
  - Update da_funk (3.24.1);
  - Update array list of files that shouldn't be removed on clear;
  - Added new layout to be used on log send process;
  - Refactor on LogControl#upload;
  - LogControl#layout;
  - Present better interface in the log send;
  - Avoiding user to input zero amount;
  - Implemented MediaConfiguration#gprs_default.

### 7.10.0 - 2020-07-25

- Update da_funk (3.24.0)
  - Added Device::Signature class;
  - Added support of converting signature after updating params.dat;
  - Added support to network state on status bar;
  - Added support to physical number keys on virtual keyboard.
- update main (3.49.0)
  - Validates if menu returned KEY_TIMEOUT to avoid crash app;
  - Fixed title on logs menu;
  - Removed LogControl#enabled;
  - Fixed call to LogControl#write_keys;
  - Keep maximum 7 log files;
  - Delete log in case user has canceled send;
  - Update cloudwalk_handshake (1.16.0);
  - Added ability of dynamic log interval send definition;
  - Do not return nil on Fixnum comparison to avoid exception;
  - Fixed date comparison on LogControl#purge;
  - Emit sound to warning the user that logs are about to be send;
  - Check if file exists before trying to delete or send it;
  - Fixed log file path;
  - Fixed handler to check battery level;
  - Added new status bar images;
  - Added method CloudwalkSetup#update_process_in_progess?;
  - Added CloudwalkSetup#boot_layout method;
  - Fixed file path on :file_exists handler;
  - Call to LogControl purge in the end of handler execution;
  - Added layout files to 6 steps update process;
  - Call to cw_infinitepay_app to complete update;
  - Updated emv table backup;
  - Fixed app crash on LogsMenu;
  - Update cloudwalk_handshake (1.18.0);
  - Update da_funk (3.24.0).

### 7.9.0 - 2020-06-24

- Enable memory profiling on main execution
- Update SDK
  - Update BC to verison 1.39;
- Update main 3.44.0
  - Support new ThreadChannel interface (only read/write);
  - Change GC strategy to freak mode (execute every 2 minutes a full GC in all threads);
  - Remove stop of engine if memory consumption is to high;
  - Remove stop of engine if every 1440 minutes;
  - Remove thread status bar;
  - Rename PaymentChannel::client to PaymentChannel::current;
  - Cache CwMetadata on boot time;
  - Check status bar on communication thread;
  - Refactoring communication thread loop:
    - Adopt new ThreadScheduler.execute interface (without sending thread id);
    - Do not call Listener if payment channel connected
  - Update da_funk (3.20.0)
    - Rename PaymentChannel::client to ::current;
    - Fix status bar change link to cache old value;
- Update mruby-context
  - Refactoring ThreadChannel abstraction;
    - Replace all methods `channel_*` and `queue_*` for write and read only;
    - Support id per write/read event;
  - ThreadScheduler: On not cacheable execution return nil if ‘cache’;
  - Fix mrb_thread_pub_sub_s_publish return;
  - Implement Contextlog in pure C;
  - Bug fix memory leak on queue creation;
  - Check CommunicationThread->status on execution response return;
  - Ensure NULL value to stop and start thread;
  - Refactoring context_thread pause, continue and message passing;
  - Execute GC right after every app execution;
  - Enable memory profiling on all applications;
  - Clean up connThreaadEvents on thread_scheduler_stop;
  - Support PaymentChannel::current syntax;
  - Remove status bar thread;
  - Fix channel id parameter on read operation;
  - Refactor thread scheduler execution function;
  - Use less chars form Time on thread channel generation id;
  - Channel now mock `handshake?` function to true;
  - Major refactoring on thread scheduler
    - Refactoring between threads command execution, change strategy to reduce memory, and adopt malloc/realloc to the minimal runtime use;
    - Remove thread status command and response;
    - Refactor function sessions a rename some of them;
    - Initialize all pointers with NULL (it was a big memory problem);
    - Remove execution time of waiting;
    - Implement ThreadScheduler::_command_once;
  - Do not clear `connected?` command cache on execution thread;
  - Bug fix message Len max between thread channels;
  - define CHANNEL_MAX_MSG_SIZE and THREAD_COMMAND_MAX_MSG_SIZE;
  - Fix memory initialisation for pause/continue thread events;
- Update main 3.45.1
  - Update funky-emv 1.3.0.
    - Added support to retrieve contactless apps
    - Implemented Device::EMVRow#ctls?
    - Check false or empty? on credit and debit appplications
- Update da_funk (3.21.0)
 - Removed unnecessary processing method call;
 - Status bar refactored:
  - Removed link icon;
  - Added support to SLOT_MEDIA to print WIFI or GPRS;
  - Renamed SLOT_CONNECTION to SLOT_SIGNAL_LEVEL;
  - Added support to SLOT_BATTERY_PERCENTUAL to print percentual of battery level;
  - Renamed SLOT_BATTERY to SLOT_BATTERY_LEVEL;
  - Update battery and wifi images;
  - Added BATTERY_PERCENTAGE_IMAGES;
  - Show searching icon when network is not connected;
- Added support to virtual keyboard;
- Added support to touchscreen event on DaFunk::Helper#menu;
- Added support to return timeout parameter on DaFunk::Helper#menu when timeout is achieved;
- Update funky-emv 1.3.0.
- Update main (3.46.0)
  - Updated status bar images;
  - Removed unnecessary images from resources/shared;
  - Updated AdminConfiguration::KEEP_FILES;
  - Added boot welcome image;
  - Added support to emv contactless timeout and user canceled messages;
  - Update da_funk (3.21.0).
- Update da_funk (3.21.2)
  - Fixed timeout return on DaFunK::Helper#menu, it should return Device::IO::KEY_TIMEOUT not options[:timeout];
  - Set cloudwalk endpoint as default.
- Update main (3.46.1)
  - Update da_funk (3.21.2);
  - Update funky-emv (1.3.1)
    - Replace emv_wait to emv_processing image display.
  - Fixed app crash if timeout or cancel is returned on LogsMenu.
-  Added new BC libraries to the link process;
- Fixed libs from symblinks in the AIP package. We changed the BC version, but we forgot to load the right files on the AIP;
- Update mruby-emv;
  - Added start_check_event and check_event methods;
  - Added start_check_event and check_event output return as an array.;
  - Fixed menu selection for timeout when there's no menu image;
  - Fixed return nil statement (return and return nil is the same thing);
  - Implemented workaround to solve emv application selection problem when timeout is achieved and return correct value.
- Update da_funk (3.22.0)
  - Update cloudwalk_handshake (1.14.0);
  - funky-emv (1.4.0);
- Update main (3.47.0)
  - Update cloudwalk_handshake (1.14.0);
    - Added authorizer cloudwalk staging url;
    - Fixed logging message sent and received size and also nsu transaction for infinitepay operation.
  - Update da_funk (3.22.0)
    - Update cloudwalk_handshake (1.14.0);
    - funky-emv (1.4.0);
  - Update funky-emv (1.4.0)
    - Since PAX start_get_card and get_card started to block the EMV flow, now it was needed to implement start_check_event and check_event in order to retrieve the non blocking lost behaviour.
    - Fixed bug on check_event, it wasn't considering when operator was pressing CANCEL.
- Update mruby-context
  - Refactoring PubSub to avoid publish event on your on subscription;
  - Change events queue messa slot creation strategy;
  - limit CHANNEL_MAX_MSG_SIZE to dequeue;
- Update da_funk (3.23.0)
  - Remove ThreadPubSub publication before attach;
  - Update funky-emv (1.4.1).
- Update main (3.48.0)
  - Do not stop ThreadScheduler on media configuration;
  - Cache ThreadPubSub id on payment_channel listener;
  - Update some header icons;
  - Only clear display on ctls amount if timeout or user cancel;
  - Reboot emv interface on magnetic finish;
  - Update funky-emv (1.4.1);
    - Update cloudwalk_handshake (1.14.0).
  - Update da_funk (3.23.0)
    - Remove ThreadPubSub publication before attach;
    - Update funky-emv (1.4.1);
- Update main (3.48.1)
  - Update cloudwalk_handshake (1.15.0)
    - Added support to logging additional Http information.
- Update mruby-context
  - Support to outdate application context:
    - Implemented Kernel::mrb_start to load application in memory;
    - mrb_stop set context application as expired if it’s currently been executed;
    - mrb_eval support to check if context application is expired to restart
    And execute

### 7.8.1 - 2020-05-25

- Update main (3.41.0)
    - Adopt new THREAD_* flags and pause timeout (200 msec);
- Update main (3.42.0)
    - Change reboot timeout to 1440 minutes;
- Update mruby-context
    - Support timeout on thread pause check;
    - Thread.command only change thread status if thread status is on response status;
    - Fix thread check algorithm
        - There was a bug during the thread status check, the process was always checking the status bar, instead of communication when communication thread;
        - Refactoring constant names.
- Update main (3.43.0)
  - Update rake from 10.5.0 to 12.3.3;
  - Refactor on logs send mechanism, it's not necessary to proxy with switch anymore;
  - Update da_funk (3.18.0).
- Update mruby-context
- Updated da_funk (3.18.0)
  - Added enable_txt_ui parameter on the following methods:
   - DaFunk::ParamsDat#download;
   - DaFunk::ParamsDat#update_apps;
   - DaFunk::ParamsDat#update_app;
   - DaFunk::ParamsDat#update_file;
   - DaFunk::Helper#attach_options;
   - DaFunk::Helper#check_download_error.
- Update main (3.43.1)
 - Update Cwfile.json because now we can update main application remotely

### 7.8.0 - 2020-02-17

- Added support to 7production and 7mockup signature;
- Update da_funk (3.17.0)
 - Added support to infinitepay dns on config.dat file;
 - Update cloudwalk (1.15.0);
 - cloudwalk_handshake (1.13.0);
- Update main (3.39.0)
  - Added support to infinitepay endpoint configuration on cloudwalk menu;
  - Update cloudwalk_handshake (1.13.0);
  - Clear queue of touch events;
  - Increase range of touch to start contactless transaction;
  - Fixed error when amount is KEY_TIMEOUT on InputTransactionAmount;
  - Check battery level each 5 minutes in order to warning the user that the battery is low when it's in idle;
  - Increase timeout on getxy_stream to avoid click many times;
  - Update da_funk (3.17.0);
- Update main (3.40.0)
 - Added handler to also start ctls transaction pressing key number.

### 7.7.0 - 2020-01-31

- Update mruby-pax;
- Update main (3.38.0)
  - Use infinitepay logo as default image;
  - Removed amount text from main display when ctls is enabled;
  - Added :touchscreen event listener;
  - Refactored InputTransactionAmount class. CTLS Amount is not being captured from idle anymore, now this call is based on a touch screen event;
  - Added event handler for contactless transactions;
  - Set getc and with getxy_stream timeout to 100ms to have a better UX;
  - Change reset time from 24hrs to 5hrs;
  - Update da_funk (3.16.3)
    - Changed setting emv_input_amount_idle to emv_contactless_amount.
  - Update cloudwalk (1.15.0);
  - Update cloudwalk_handshake (1.12.0)
    - Add metadata information in transactions payload.

### 7.6.2 - 2020-01-17

- Fix version description.

### 7.6.1 - 2020-01-17

- Update main (3.36.0)
    - Simple bump version.

### 7.6.0 - 2020-01-17

- Update main (3.22.0)
    - Replaced executable_apps for ruby_executable_apps that only pre loads ruby applications;
    - Add main to manager with the version 1.0.0;
    - Add message to main application update reboot;
    - Update funky-emv (1.0.0)
        - Support CTLS emv table;
        - Support CTLS operation;
        - Added CTLS attribute in init_info structure;
    - Update funky-emv (1.1.0)
        - Support to load information from Json on init_data structure;
        - Support to build custom parameters on EmvTransaction.params.
    - Update posxml_parser (2.20.0)
        - Update funky-emv (1.0.0);
    - Update posxml_parser (2.21.0)
        - Support to send magnetic parameters through EmvTransaction;
    - Update cloudwalk_handshake (1.4.2)
        - Fixed host value to api connection;
    - Update da_funk (3.8.1)
        - Fix ISO8583 binary bitmap generation to CRUBY;
    - Update da_funk (3.8.2)
        - Fix ISO 8583 HEX Bitmap generation;
        - Implemented ParamsDat::ruby_executable_apps;
    - Update da_funk (3.8.3)
        - Added emv_input_amount_idle parameter on config.dat;
    - Update da_funk (3.9.0)
        - Support to uncompress main application and reboot after it;
- Update main (3.23.0)
    - Added InputTransactionAmount class to handle input amount on the idle screen and support CTLS from idle;
- Update main (3.24.0)
    - Update da_funk (3.10.0)
        - Do not raise load error when cloudwalk_handshake doesn’t exists;
        - Support to app set on PaymentChannel;
        - Set PaymentChannel application on Device::System::klass=;
        - Support CwHttpEvent on PaymentChannel;
    - Update da_funk (3.10.1)
        - Fix application set loop on PaymentChannel and System;
    - Update da_funk (3.10.2)
        - Fix main application detection on app update;
        - Support cloudwalk_handshake (1.6.0);
    - Update cloudwalk_handshake (1.5.0)
        - Implement CwHttpEvent class to handle CloudWalk http events;
        - Implement CwInfinitepayHostSetting.authorizer_allowed_application? to check applications allowed to transact on authorizer;
        - Implement CwInfinitepayHostSetting.api_allowed_application? to check applications allowed to transact on infinitepay api;
    - Update cloudwalk_handshake (1.6.0)
        - Move CwHttpEvent to Cloudwalk::HttpEvent and add tests;
    - Update posxml_parser (2.22.0)
        - Show message processing after card swiped. After swipe the card it takes some time to the terminal to return a feedback because it is parsing some formations. It can cause confusion to the user. To avoid this we show a messag
        - Parse card informations and send to emv struct with this we can get:
            - Track1(if exists);
            - Track2;
            - Pan;
            - Service code;
            - Expiration date;
            - Cardholder name(if exists);
            - Card type;
            - Result of operation;
        - Send card info on emv struct;
    - Update funky-emv (1.2.0)
        - Implement pre selection of credit and debit applications;
    - Update funky-emv (1.2.1)
        - Fixed issue with magnetic card swiped, shared library is not returning magnetic stripe data;
    - Send Magnetic object instead track2 only on Magnetic Handler triggering;
- Update mruby-context
    - Added rescue for ArgumentError to prevent error on app that doesn't receive parameters;
    - Execute system reload on every execution;
    - Increased ThreadScheduler exchange buffers to 50k in order to avoid memory leaks;
    - Update application Klass on app execution;
    - Support application set between threads;
    - Bug fix check if CommunicationThread exist to schedule command;
    - Bug fix ThreadScheduler application configuration return;
    - Support Cloudwalk::HttpEvent;
- Update mruby-emv
    - Added support to render image on input card.
- Update da_funk (3.11.0)
  - Added support image or text display when booting a new runtime;
  - Remove cache ruby application mechanism
- Update mruby-context
  - Remove cache ruby application mechanism
- Update cloudwalk_handshake (1.8.1)
  - Added support of Authorizer production URL
- Update main (3.25.0)
  - Remove cache ruby application mechanism
- Update posxml_parser (2.24.0)
  - Support of scheduling tasks from ruby applications through json file.
- Update main (3.26.0)
    - posxml_parser (2.24.1)
        - Fix on scheduler rb apps. The handler should search for cw_app_schedule.json file in the root of the application folder;
    - da_funk (3.11.1)
        - Fixed method call on ISO8583Exception rescue;
    - da_funk (3.12.0)
        - Added DaFunk::Helper#wait_touchscreen_or_keyboard_event;
        - Added Added DaFunk::Helper#menu_image_touchscreen_or_keyboard;
    - da_funk (3.12.1)
        - Bug fix local jump error: unexpected return. Error found on methods added to touch screen operations (Helper);
- Update main (3.27.0)
    - da_funk (3.12.2)
        - Bug fix undefined method 'x' on parse_touchscreen_event. This method was not receiving x and y which were local variables;
- Update mruby-emv
    - Added touchscreen support in the callback application selection;
- Remove memory leaks on mruby-miniz, mruby-context, mruby-socket, mruby-io, mruby-require and mruby-tempfile;
- Update mruby-pax
    - Support OsPiccIsoCommand on MifareCard interface;
- Update mruby-context
    - Fix memory leak between thread command execution;
    - Wait other thread collect response. On thread command execution it’s necessary to wait until any other thread collect the response to try scheduling a new command;
    - Define default value to cache ThreadScheduler.command as nil;
    - Return true as string on ThreadScheduler.command;
- Update main (3.28.0)
    - Update da_funk (3.12.3)
        - Duplicate string before mrb_eval to avoid possible memory leak;
- Update mruby-json
- Update mruby-context
    - Bugfix memory leak adopting mrb_load_nstring_cxt on mrb_eval. This avoid consider a NULL pointer string;
- Update mruby-pax
    - Add Kernel.touch_clear;
- Update main (3.29.0)
    - Update da_funk (3.13.0)
        - Added funky-mock library;
        - Add status bar spinner to system update;
        - Support background update;
        - Refactoring touch events handling;
    - posxml_parser (2.25.0)
        - Move file_exists Listener to main application;
    - Added new :file_exists handler to update applications;
    - Add system update icon message;
    - Add support to system update in background;
- Update main (3.30.0)
    - Update cloudwalk_handshake (1.9.0)
        - Add check_update to see if there's a notification to update system or application comming from header;
- Update mruby-pax
    - Update MifareCard.command strategy;
- Update main 3.30.1
    - Update funky-emv (1.2.2)
        - Fixed tags size calculation;
- Update main 3.31.0
    - Update da_funk (3.13.1)
        - Update funky-emv (1.2.2);
        - Updated cloudwalk_handshake (1.9.0);
- Update mruby-pax
    - Support OsPiccActive on MifareCard;
- Update mruby-pax-network
    - check if communication was initialized to execute network commands;
    - Refactoring Wifi::connected? returning an array instead of set all the instance variables;
    - Fix wifi rssi conversation to signal percentage;
    - Improve network initialisation control storing the result;
- Update mruby-context
    - Remove communication update event publish;
- Update da_funk (3.14.0)
    - Notify all threads that modifications on network was made;
    - Support Device::Setting::network_init to improve network initialisation control;
    - Load metadata after successfully attach;
    - Update cloudwalk_handshake (1.10.0);
- Update main (3.32.0)
    - Display message before wait to stop communication on network configuration;
    - Create $thread_name global variable;
    - Update cloudwalk_handshake (1.10.0);
    - Update da_funk (3.14.0);
- Update main (3.33.0)
    - Added ruby apps tasks scheduler handler;
    - Changed method name setup_app_events to setup_keyboard_events_from_rb_apps;
    - Changed file name CwKeys.json to cw_keys.json to have a name pattern;
    - Added :boot handler event listener;
    - Update posxml_parser (2.26.0);
- Update mruby-pax
    - Support OsPiccTransfer on MifareCard;
- Update main (3.34.0)
    - Added exist validation when delete shared/system_update folder;
    - Update cloudwalk_handshake (1.11.0)
    - Update da_funk (3.15.0)
- Update da_funk (3.15.0)
    - Load/update config.dat file before set payment channel attempts
        
### 7.5.3 - 2019-06-13

- Cache main application to future execute call.
- Update main (3.21.0)
    - Update cloudwalk_handshake (1.4.1)
      - Fixed wrong host and port values for HTTP connection.

### 7.5.2 - 2019-06-09

- Update mruby-context
    -  Fixed memory leak at application_name when alloc or search instances.

### 7.5.1 - 2019-06-06

- Added a new way to start the runtime.

### 7.5.0 - 2019-06-06

- Update mruby-context
    - Refactoring mrb_eval supporting mruby instance cache. Implement instance structure to store every mrb pointer limited to 20 instances and add Kernel.mrb_stop to remove any instance from pointer instance list;
    - Refactoring ruby mechanism to cache applications, divide it in two steps, start (loads and requires) and execute (Main.call);
- Update mruby-pax
    - During print thread kill add thread.alive? check in order to validate if there's a thread running before the thread join;
- Update main (3.20.0)
    - Update cloudwalk_handshake (1.4.0)
        - Added CwInfinitePayHostSetting class all settings related with infinitepay environments;
        - Refactoring CwHttpSocket to support infinitepay-authorizer;
    - Update da_funk (3.8.0)
        - Do not send host/port information to CwHttpSocket, let it deal with host and port config from config.dat and/or params.dat;
        - Added infinitepay_authorizer and infinitepay_api on config.dat;
        - Divide Runtime execution in two steps, start (application loading) execute (application execution);
        - Support to cache an application after downloading;
    - Update funky-emv (0.25.0)
        - Replaced waiting to emv_wait;
        - Fix tag 4F removal on EmvSharedLibrary;
    - Update funky-emv (0.26.0)
        - Refactoring json parameters use on EmvTransaction::open to support emv parameters share between ruby applications;
        - Store selection result in init_info struct as result key;
    - Update posxml_parser (2.19.0)
        - Support to send json parameters at posxml_execute, and add support to share emv data;
        - Implemented transfer of magstripe data between ruby applications;
- Update main (3.35.0)
    - Update da_dunk (3.15.1)
        - Just removed some debug points.

### 7.4.15 - 2019-05-22

- Update mruby-context
    - Added support to get http code status on thread interface;
- Update main (3.19.0)
    - Refactoring emv Listener supporting Funky-emv (0.24.0), and update emv_enabled flag use to define allowed as default;
    - Fix system update package count and improve interruption ux;
    - Add backup emv table to support funky-emv (0.24.0);
    - Update funky-emv (0.24.0)
        - Support backup emv_acquirer_aid load;
        - Implement EmvTransaction::boot to open, clean and load tables;
        - Implement EmvTransaction::reboot to close and open handle;
        - Implement EmvTransaction::set_initial_data to define time operation;
    - Update cloudwalk_handshake (1.3.0)
        - Support http code status on CwHttpSocket;
    - Update da_funk (3.7.0)
        - Added support to get http code status using payment channel interface.

### 7.4.14 - 2019-05-21

- Update main (3.18.0)
    - Do system reload on main thread after communication update to fix communication fallback operations;
    - Update da_funk (3.6.0)
        - Avoid memory leak on EventListener, avoid cleaning memory duplicating object;
        - Check if ContextLog object exists on ISO8583;
- Update mruby-pax-network
    - Fix SIM ID read on PAX’s S920, D200 and D195, specifically on D200 the message response is longer than others models;
- Update mruby-context
    - Remove ContextCommunicationChannel fallback responsiblity;

### 7.4.13 - 2019-05-13

- Update main (3.17.0)
    - Update da_funk (3.5.0)
        - Fix time range exception on schedule;
- Update mruby-context
    - Add timeout to exception message on production.

### 7.4.12 - 2019-05-13

- Bump.

### 7.4.11 - 2019-05-13

- Update main (3.16.0)
    - Update da_funk (3.4.0)
        - Do not remove old files and application on params.dat.

### 7.4.10 - 2019-05-13

- Update main (3.15.0)
    - Update da_funk (3.3.1)
        - Mock Device::Setting.logical_number from System if empty.

### 7.4.9 - 2019-05-10

- Update main (3.14.0)
    - Add EventHandler for payment_channel at comm thread. This enable payment_channel Listener check;

### 7.4.8 - 2019-05-10

- Update main (3.13.0)
    - On communication thread check communication and payment_channel listener;
    - Update funky-emv (0.23.5)
        - Fix acquirer_id addition at EmvSharedLibrary.

### 7.4.7 - 2019-05-07

- Update mruby-emv
    - Do not specify Platform names at pinpad;
    - Support Pinpad::encrypt to fix 3des encryption;
 - Update mruby-context
     - Fix thread scheduler information binary exchange to allow download binary information via payment channel;
- Update main (3.12.0)
    - Refactoring fallback communication routine. Create another Listener to handle only communication issues;
    - Check all possible listener on communication thread;
    - Added emv_wait messages;
    - Update funky-emv (0.23.4)
        - Fix possible format error at acquirer id on EmvSharedLibrary;
    - Update da_funk (3.3.0)
        - Remove communication errors from PaymentChannel;
        - Remove unnecessary MAC address log;
        - Implement ConnectionManager.check (from PaymentChannel).

### 7.4.6 - 2019-04-16

- Update main (3.11.0)
    - Update cloudwalk_handshake (1.2.3)
        - If infinitepay_host return body if received key unavailable.

### 7.4.5 - 2019-04-16

- Update main (3.10.0)
    - Update funky-emv (0.23.3)
        - Bug fix setup return (integer type needed) when pax.

### 7.4.4 - 2019-04-16

- Update mruby-emv
    - Add timeout between input pin form to fix UI glitch
- Update main (3.9.0)
    - Update funky-emv (0.23.2)
        - Remove unnecessary usleep during pin entry.

### 7.4.3 - 2019-04-15

- Update main (3.8.0)
    - Update funky-emv (0.23.1)
        - Fix image corruption adopting a wait time between input display at FunkyEmv::UI::display.

### 7.4.2 - 2019-04-15

- Update main (3.7.0)
    - Update posxml_parser (2.18.0)
        - Move PosxmlParser::FileDbCache.fresh to exit only;
        - Support _execute0 method on translation execution, that feature is capable to call declaration method once saving some time on execution time;

### 7.4.1 - 2019-04-11

- Update mruby-emv
    - Fix emv app selection image display on pax;
    - Fix Pinpad::key_kcv and Pinpad::key_ksn on PAX;
- Update main (3.6.0)
    - Update da_funk (3.2.1)
        - Fix Dir removal on Application.delete;
    - Update posxml_parser (2.17.0)
        - Bugfix ruby app execution from non PosxmlParse instance;
        - Allow ruby app to be executed on emv handler.

### 7.4.0 - 2019-04-09

- Update main (3.5.0)
    - Add keymap.dat;
    - Update funky-emv (0.23.0)
        - EmvSharedLibrary: Reduce timeout on process loop getc;
        - EmvSharedLibrary: display waiting image after go on chip;
        - Support icc detection to PAX EmvSharedLibrary devices;
        - Always EmvSharedLibrary to EmvTransaction.

### 7.3.2 - 2019-03-28

- Support NO_MAIN_BMP flag;
- Update main (3.4.0)
    - Update cw_apns.dat.

### 7.3.1 - 2019-03-27

- Update mruby-context
    - Bug fix wrong transaction response between threads cleanning recv queue before enqueue send;
- Update main (3.3.0)
    - Change default application update period to 360 hours;
    - Change default application update interval to 120 hours;
    - Change system update strategy:
        - Change default interval to 360 hours;
        - If params.dat system_update_interval 0 disable system update;
    - Update posxml_parser (2.16.0)
        - Remove clean display before posxml execution;
        - Remove payment channel extra connection check;
        - Add emv_acquirer_aids file check;
    - Update funky-emv (0.22.0)
        - Refactoring displays and wait screen timeout to speed up transaction flow;
    - Update cloudwalk_handshake (1.2.2)
        - Bug fix add dependency funky-simplehttp on gemspec and avoid exception on gem use.

### 7.3.0 - 2019-03-14

- Update main (3.2.0)
    - Update da_funk (3.2.0)
        - Support menu_image helper that display image for menu;
    - Update funky-emv (0.21.0)
        - Support custom selection image;

### 7.2.0 - 2019-03-14

- Update main (3.1.0)
    - Bug fix injected keys log typo;
    - Add support to params.dat flag log_upload_enabled.
    - Execute upload log routine every 24 hours;
    - Refactoring upload logs routine:
        - Upload the log from yesterday;
        - User would be able to cancel upload log in 5 seconds;
        - Minimal fixes and typos.
    - Update cloudwalk_handshake (1.1.0)
        - Update cloudwalk (1.14.1);
        - Implement LogRegiser and MessageParser to log socket read/write operations.
    - Update cloudwalk_handshake (1.2.0)
        - Bug fix LogRegister sent size log information;
        - Rename LogRegister.cw_websocket_trasction_nsu to log_websocket_trasction_nsu and implement support to receive a buffer that could contain a NSU information;
        - Bug fix MessageParser::identify removing http verb match;
        - Support CwHttpSocket logging.
    - Update cloudwalk_handshake (1.2.1)
        -  Bug fix LogRegister handshake size log;
        -  Refactoring MessageParser
            - Add 2 more NSU test scenarios;
            - Refactoring identification matching strings;
            - Support to return CwHttp and WebScoket handshake transaction information;
            - Rescue any exception on must use executions;
            - Bug fix JSON NSU extraction to bigger informations (16 bytes).
        - Rename LogRegiser nsu method to LogRegister::nsu;
        - Refactoring LogRegister debug messages;
        - Rescue LogRegister exceptions;
        - Refactoring log read/write strategy do not store open message size, store encrypted, and real, message size instead refactoring log read process to avoid double logging;
    - Update da_funk (3.1.0)
        - Replace host config for http (switch-http.cloudwalk.io to pos.cloudwalk.io)
    - Update da_funk (3.1.1)
        - Bug fix attach helper loop image and decrease display time to 200ms;
        - Bugfix flag PaymentChannel::transaction_http use PaymentChannel didn’t change to payment channel approach when demand;
        - Bug fix extend timeout to PaymentChannel handshake.

### 7.1.0 - 2019-02-28

- Update main (3.0.0)
    - Support to close http socket at the end of an event;
    - Force http socket creation during write event on thread communication;
    - Update README with new parameter transaction_http_enabled;
    - Update posxml_parser (2.15.0)
        - Check if socket is connection process to consider connected;
    - Update da_funk (3.0.0)
        - Replace payment channel interface from WebSocket to HTTP;
        - Support config.dat parameters `transaction_http_enabled`, `transaction_http_host`, `transaction_http_port`;
    - Update cloudwalk_handshake (1.0.0)
        - Implement CwMetadata to support request metadata, divide metadata in 2 levels, level 1 with all the values, and level 2 with only Media, Geo-Cell-Info, Signal and Battery;
        - Implement CwHttpSocket to support http transaction;
        - Support http host at SSL endpoint configuration to enable new ciphers;
        - Refactoring CwHttpSocket to support payment channel API;
        - Support to send transaction to infinitepay directly CwHttpSocket only, and configured by ParamsDat.file[“infinitepay_host”].
- Update mruby-context
    - Bug fix ThreadScheduler command and execution block every command was blocked until execution ends;
    - ContextCommunicationChannel clear ThreadScheduler cache on close method;
    - Implement connection cache if connect command was called necessary implementation on ContextCommunicationChannel::connect ::connected? ::handshake?;
    - Rename listen to pubsub_listen on ThreadScheduler necessary to avoid compilation error;
    - Addd DaFunk::Helper::StatusBar.valid? method for the status bar checking method on the thread_scheduler.rb, that implementation is not necessary on ingenico tetra terminals because it implements native status bar.
- Update mruby-miniz
    - Refactoring inflate/deflate default parameters to follow web socket standards;
- Update mruby-pax
    - Add MifareCard::close
- Update mruby-polarssl
    - Fix typoe of mruby-io and mruby-socket dependency;
    - Fix type of mruby-io and mruby-socket dependency;
    - Fix memory leaks found by sanitizer;
    - Keep dependencies default;
    - Clone mruby 1.3.0 to perform tests;
    - Update polarssl (mbedtls) from 1.3.11 to 2.16.0;
    - Addd mruby-print as dependency and refactoring compilation, compile every file inside of polarssl/library/;
    - Refactoring pk parse curve strategy adopted functions mbedtls_ecp_curve_info_name to check group id from curve;
    - Port new mbedtls SSL/TLS socket creation mechanic support to mbedtls conf struct and new initializers;
    - Update README and license;
    - Remove COPYING and COPYING.LESSER;
    - Add mbedtls_ssl_handshake in order to mbedtls programs that call should be in loop checking if it keep in progress;
    - Support MRUBY_MBEDTLS_DEBUG_C to enable debug;
    - Support PolarSSL::SSL.set_hostname;
    - Update README with debug section;
    - Remove warnings;
- Update mruby-socket
    - Remove cloudwalk endpoint enforcement.

### 6.7.2 - 2019-02-19

- Update mruby-context
    - Restart application if it crashs.

### 6.7.1 - 2019-02-17

- Update main (2.14.1)
    - Update da_funk (2.7.1)
        - Bug fix set payment channel limit disable as default;

### 6.7.0 - 2019-02-17

- Reload the runtime if flag is configured;
- Turn on memory mapping on main runtime;
- Update main (2.13.0)
    - Update posxml_parser (2.14.0)
        - Add SysNm tag to iso20022 acceptor authorization request, this tag is responsible sender identification;
- Update main (2.14.0)
    - Adopt GC.start run on status bar thread;
    - Bug fix stuck screen before persist new media config;
    - Run GC.star every 10 minutes on communication thread;
    - Run GC.star every 10 minutes on main thread;
    - Reload runtime engine every 24 hours and if memory reaches 14mb;
    - Call PaymentChannel.connect on mag and emv listener events, this start the payment channel creation (on communication thread) even if limit is exceed;
    - Force payment channel creation if it doesn’t exists on comm thread. Logic is trigged if a write message (from main thread) is queued;
    - Update da_funk (2.6.0)
        - Support to Device::Runtime::reload on Engine stop;
    - Update da_funk (2.7.0)
        - Execute ThreadScheduler::keep_alive every engine check;
        - Refresh every file on every FileDb set method if key is boot, this is a temporary fix to avoid edit problem between threads;
        - Add Device::Setting attributes, payment_channel_attempts - To count channels in a day; payment_channel_date - Connection day;
        - Implement Device::Setting::payment_channel_set_attempts, it’s a simple helper to set both payment_channel_date and payment_channel_attempts;
        - Implement channel connection limit configuration;
- Update mruby-pax
    - Support PAX::Runtime::reload to allow terminal to restart runtime;
- Update mruby-context
    - Replace string creation function in ThreadSchedule::_command, from mrb_str_new_cstr to mrb_str_new (fixed size) to try avoid memory leak;
    - Turn on memory mapping on runtime by Vm class
    - Change Thread status to stop when thread died at ThreadScheduler;
    - Implement thread keep alive system;
    - Bug fix ThreadScheduler::execute rescuing and logging error, this avoid the runtime to be blocked;
    - Bug fix ThreadScheduler::execute typo when execute connect.

### 6.6.6 - 2019-02-07

- Update main (2.12.0)
    - Bug fix during communication update between threads to only close the socket if media configuration was changed;
    - Update da_funk (2.5.1)
        - Fix EventHandler rescheduler when dealing with slot;
    - Update posxml_parser (2.13.1)
        - Adopt a better communication check system on cw_payment_channe.dat call posxml_payment_channel_check function.

### 6.6.5 - 2019-02-06

- Update main (2.11.0)
    - Update posxml_parser (2.13.0)
        - Implement booting check during payment channel check;
- Update mruby-context
    - Implement booting variable to communication start up.

### 6.6.4 - 2019-02-05

- Update mruby-pax
    - Refactor common emv functions to emv.h get_rgba(), getAsteriskSize(), fix_x() and fix_y();
    - Bug fix PIN plain entry font setup, race conditions during pin requires to configure font in the callback cEMVGetHolderPwd();
- Update main (2.10.0)
    - Update da_funk (2.5.0)
        - Bug fix EventHandler with slot configuration (schedule execution impact, example application or system update)
            - Fix timestamp when configuration has changed;
            - Fix execution between boots;
    - Update funky-emv (0.20.2)
        - Bug fix blanked screen before pin entry on PAX.

### 6.6.3 - 2019-01-23

- Update main (2.9.0)
    - Implement CloudwalkUpdate.system routine, first implementation of UX system update improvement process;
    - User can cancel automatic update in 10 seconds;
    - Update handlers to update and system update; - Set default update interval to 24 hours; - Set default system update interval to 168 (week).

### 6.6.2 - 2019-01-14

- Update mruby-pax-network
    - Fix mac_address ifname check and fix method typo
- Update main (2.8.0)
    - Add MAC address to communication show;
    - fix symbol name on case;
    - Update da_funk (2.4.0)
        - Support Device::Network.mac_address;
- Update main (2.8.1)
    - Update posxml_parser
        - Support to return macaddress at system.info instruction;

### 6.6.1 - 2019-01-08

- Rollback mruby-miniz

### 6.6.0 - 2019-01-08

- Update mruby-pax-network
    - Implement PAX::Network.mac_address;
    - Fixed cache on connect process;
    - Implement PAX::Network.mac_address;
- Update mruby-miniz
    - Change inflate/deflate parameters to default values;
    - Add mruby-pack dependency;
    - Support parameters on deflate operation;
- Update main (2.5.0)
    - Update posxml_parser (2.9.0)
        - Fix network.cloudwalkhandshake variable type declaration;
        - Fix integer type check at posxml compilation, support camelcase declarations;
        - Update test xsd from PosxmlParser version;
        - Fix instruction not found check to instruction with parameters;
        - Supporr to system.getlog instruction compilation;
- Update main (2.6.0)
    - Update posxml_parser (2.10.0)
        - During translation lowercase first letter function;
- Update main (2.7.0)
    - Update da_funk (2.3.0)
        - Implement Device::Setting.metadata_timestamp;
        - Implement access to configuration at Device::Setting;
    - Update posxml_parser (2.11.0)
        - Add sale context tag and it's attributes at ISO20022 message, this tag is adopted by the sub acquires to identify the merchant;
    - Add apps and system update to execute options.

### 6.5.0 - 2018-12-12

- Support d195 on display initialization;
- Fix pixel left when clear char in any form;
- Update SDK
    - Update TermAssist 3.0.9.5418;
- Update mruby-pax
    - Support d195 model add keys; columns and lines configuration; model name.

### 6.4.1 - 2018-12-05

- Update mruby-pax
    - Fix s920 FUNC and ALPHA navigation keys invertion;

### 6.4.0 - 2018-12-04

- Update main (2.4.0)
    - Refactoring PAX S920 key map inverting ALPHA by FUNC;
    - Update cloudwalk (1.11.4);
    - Update da_funk (2.2.0)
        - Support pausing communication on Network::scan;
- Update mruby-pax
    - Support new ALPHA and MENU S920 key layout;
    - Fix ICC read after EMV library update(v651), added sam slot initialization on EMV library initialization;
- Update mruby-pax-network
    - Add timeout to call connected after media initialisation that call could block all thread executions and its been cached with 1 (connecting) while waiting for timeout to access SDK;

### 6.3.0 - 2018-11-28

- Update EMV Library to v651;
- Update mruby-pax;
    - Do not call getc on communication thread;
- Update mruby-context
    - Bring ThreadScheduler from cloudwalkio/main;
    - Support to ThreadScheduler set pause status;
    - Define DaFunk::PaymentChannel.client on every runtime setup;
    - Implement ThreadPubSub class to handle notification between threads;
    - Ensure continue on ThreadScheduler::pausing;
    - Publish communication update on communication thread pause;
- Update main (2.2.0)
    - Review key_main events to link2500 terminals.
    - Update posxml_parser (2.8.5);
        - Fresh cache variable in ruby execution;
    - Update da_funk (2.0.2);
        - Fix system update removing file existence validation because it could be a not valid path;
    - Update da_funk (2.0.3);
        - Fix I18n print and translate to check line and column;
    - Update da_funk (2.0.4);
        - Do not print last if not in communication thread;
        - Replace sleep by getc at ParamsDat download functions;
    - Update funky-emv (0.20.1);
        - Refactoring EmvSharedLibrary to check tag 4F after 9F06 at go on chip process to return AID;
- Update main (2.3.0)
    - Support ThreadScheduler.pause at communication thread to not execute any event handler during other threads connection attempts;
    - Move ThreadScheduler to mruby-context;
    - Check if communication thread is sleeping before checking any communication object;
    - Remove DaFunk::PaymentChannel.client definition at call and move to mruby-context;
    - Support to ThreadPubSub subscription performing system reload on communication update event;
    - Update da_funk (2.1.0);
        - Support to thread pausing during Network.attach;
        - Ensure clear on PaymentChannel::close!;
    - Update posxml_parser (2.8.6);
        - Fix parseticket xsd;
        - Improve VariableTypeError message to highlight type;

### 6.2.2 - 2018-10-29

- Update mruby-pax
    - Fixed sleep on printer thread.

### 6.2.1 - 2018-10-26

- Update mruby-pax
    - Fixed problem calling wrong method on printer context.

### 6.2.0 - 2018-10-05

- Update mruby-context
    - Add support to Platform boot on ruby setup;
    - Support timeout in CommunicationChannel::handshake?;
    - CommunicationChannel do not set PaymentChannel client;
    - Implement CommunicationChannel commands: handshake, connect, handshake_response;
- Update main (2.1.1)
    - Increased timeout on getc;
- Update main (2.1.2)
    - Check if threads were created to stop them at ThreadScheduler;
    - ThreadScheduler only start status bar if applicable;
    - Support payment channel connect between threads;
    - Remove countdown menu from payment channel handler because this handler is being handle in thread;
    - Refactoring main execution parser;
- Update main (2.1.3)
    - Update da_funk (2.0.1)
        - Add support to create and close PaymentChannel from CommunicationChannel;
    - Update funky-emv (0.20.0)
        - Added FunkyEmv Ui to display remove card message;
- Update main (2.1.4)
    - Update posxml_parser (2.8.4)
        - Return PaymentChannel status when read cw_payment_channel.dat.

### 6.1.0 - 2018-10-03

- Update mruby-pax
    - Define Platform as PAX class to cover mruby-da-funk interface;
    - During SAK at MifareCard::uid;
- Update mruby-context
    - Fix ConnectionManagement hierarchy class call;
    - Fix ThreadSchedule cache at ThreadSchedule::command return;
- Update main (2.1.0)
    - Remove backlight control in thread;
    - Remove notification handler on communication thread;
    - Update status bar updating period from 400 to 1000ms;
    - Adopt custom notification handle at main thread;
    - Fix ThreadScheduler command cache always returning the vale to key value structure;
    - Fix fallback communication in thread communication;
    - At ThreadChannel handler loop only communicate if string is given;
    - Change strategy to thread spawn at thread scheduler to avoid missing loaded libs as da_funk execute create eval string in other scope.

### 6.0.0 - 2018-10-02

- Add mruby-errno and mruby-error;
- Update mruby-pax-network
    - Change GPRS TCP keep alive to 180 seconds;
- Update mruby-context
    - Implement ThreadScheduler to support thread spawn and communication;
    - Add CommunicationChannel as contract to PaymentChannel;
    - Implement ThreadScheduler::_command timeout;
- Update mruby-pax
    - Fix font after bitmap image print;
- Update main (2.0.0)
    - Add ThreadScheduler interface to handle threads on communication and status bar operation;
    - Support Thread scheduling on boot;
    - Stop/start communication threads between network reconfiguration;
    - Add link/unlink image to payment channel status;
    - Fix communication thread printing;
    - Update da_funk (2.0.0)
        - Support check specific listener type;
        - Adopt ThreadScheduler and stop all thread at boot end;
        - Remove status bar check from engine loop;
        - Add Support to change link/unlink payment channel image;
        - Fix IO_INPUT_NUMBERS string change at IO.get_format.

### 5.72.0 - 2018-09-10

- Update cloudwalk_handshake (0.13.2).
- Update posxml_parser (2.8.3).

### 5.71.0 - 2018-09-10

- Update mruby-context
    - Support custom log file.
- Update mruby-pax
    - Increase length of SamCard output.

### 5.70.0 - 2018-08-31

- Update mruby-pax
    - Implement custom method to print bmp bigger than 20k.
    - Fix printer thread kill printing last buffer.

### 5.69.0 - 2018-08-31

- Update mruby-pax
    - Support EMV pinbypass.
    - Support Mifare and Sam Card interface.

### 5.68.0 - 2018-08-30

- Update main (1.83.0)
    - Implement communication test at admin menu.
    - Refactoring media configuration to support device reboot and communication test after configuration.
    - Adopt da_funk confirm helper at wizard.
    - Refactoring language form at wizard to support exit.
    - Update da_funk (1.13.1).
        - Fix ScreenFlow navigation when comparing confirmation.
    - Update posxml_parser (2.8.0).
        - Support float variable compilation.
        - Add file line number to compilation error.
    - Update cloudwalk_handshake (0.13.1).
        - Add rescue ssl exception on socket operation.
        - Add rescue tcp exception on socket operation.
        - Check if socket is created at handshake and ssl handshake.

### 5.67.0 - 2018-08-17

- Add OS Update procedure to README.
- Update mruby-pax
    - Support to UTC time persistence in hwclock when configuration time_utc equals to 1.
- Update main (1.82.0)
    - Implement Notification to reboot system.
    - Reboot system after remote update.
    - Refactoring wizard and application menu check adding application update at the end of wizard and moving crc check from first ENTER press to boot, speeding up key press on idle.
    - Support update interval feature, if not configured the default is 7 days interval.
    - Add admin_communication main entry option.
    - Update posxml_parser (2.7.0).
        - Support to execute ruby application in posxml_execute.
    - Update cloudwalk_handshake (0.13.0)
        - Implement UTC mode from params.dat to generate TOTP.
    - Update da_funk (1.13.0)
        - Add DaFunk::ParamsDat::parameters_load copy of ready?.
        - ScrenFlow.confirm returns boolean.
        - Support schedule events in file if using hours parameters.

### 5.66.0 - 2018-08-13

- Update SDK
    - Add support to ITF (i25) barcode.
- Update mruby-pax
    - Add support to I25 barcode.
- Update mruby-pax-net
    - Remove any extra char at CCID extraction.
- Update main (1.81.0)
    - Update posxml_parser (2.6.1)
        - Support image at card_get_variable.

### 5.65.0 - 2018-08-09

- Add barcode library.
- Update mruby-pax
    - Implement PAX::Printer.print_barcode.
    - Bugfix remove memory leak on pin plain and verify cipher pin routines.
- Update main (1.80.0)
    - Add debug flag as false to compilation config.
    - Implement new update strategy that supports multiple files.
    - Update cloudwalk (1.10.0)
    - Update da_funk (1.12.0)
        - Do not raise exception when bitmap to be display doesn’t exists.
        - Implement Device::Priter.print_barcode.
    - Update funky-emv (0.17.2)
        - Add sleep before call pin methods to avoid problems on display and memory location of PAX EMV Kernel.
    - Update posxml_parser (2.6.0)
        - Enable FileDbCache and fix delete process.
        - Fresh any file db cache on every execute.
        - Bugfix card_read to works when EMV not enabled.
        - Do not trow exception the try to read a variable that doesn’t exists on mruby side.
        - Interface_display_bitmap returns the resulted value.
        - Bugfix input_money to works even if message is empty.
        - Implement print_barcode.

### 5.64.0 - 2018-07-03

- Update main (1.78.0)
    - Update posxml_parser (2.4.0)
        - Implement NEWDES to crypto_encryptdecrypt.
        - Fix mti message value at iso8583_analyze_message.

### 5.63.0 - 2018-07-02

- Update main (1.77.0)
    - Update funky-emv (0.17.1)
        - Set rgb 0,0,0 when font.dat doesn’t exists at Pax.

### 5.62.0 - 2018-07-02

- Update mruby-pax
    - Implement PAX::Crypto::Newdes::encrypt/decrypt.
    - Added dynamic timeout for the read serial method.
- Update mruby-pax-network
    - Implement attach via at command with imsi selection.
- Update main (1.76.0)
    - Support selection of operator when dealing with multioperator chip.
    - Update da_funk (1.11.2)
        - Fix ISO8583 bitmap parse when greater than 64 bytes

### 5.61.0 - 2018-05-25

- Update mruby-pax-network
    - Reset communication check when disconnect and connect.
    - Reset communication check when power off.
    - Multioperator selection at.
- Update mruby-context
    - Execute Device::Runtime.system_reload after boot.

### 5.60.1 - 2018-05-22

- Update mruby-pax
    - Fix timezone setting at Time.hwclock.
- Update main (1.75.1)
    - Update posxml_parser (2.3.4).
        - Disable file db cache.
    - Update da_funk (1.11.1).
        - Add Nil.integer?

### 5.60.0 - 2018-05-18

- Update mruby-pax
    - Add PAX::Pinpad::ERR_PED_NO_KEY (-3801).
    - Add some more special chars to keyboard map.
- Update main (1.73.0)
    - Remove injected keys debug.
- Update main (1.74.0)
    - add KORE apns and set alphabetical order.
    - Add 3 password attempts to menu.
    - Refactoring communication countdown.
    - Update funky-emv (0.17.0)
        - Implement cvm parse and refactoring some debugs.
        - PAX: Bug fix verify_cupher_pin return.
        - PAX: Expect ERR_PED_NO_KEY(-3801) to dukpn pin block exec.
    - Update cloudwalk (1.9.1)
    - Update posxml_parser (2.3.3)
        - Adopt simple quotes when dealing with double quotes on compilation.
- Update main (1.75.0)
    - Update da_funk (1.11.0)
        - Bug fix String.integer? when string starts with “0”
        - Increase getc timeout to 10 seconds when communication error.
        - ISO8583 convert bitmap from binary to hex and hex to binary.

### 5.59.0 - 2018-04-11

- Update mruby-pax
    - Fix display x and y when displaying bg in Device::Pinpad.pin.

### 5.58.0 - 2018-04-06

- Update main (1.72.0)
    - Check communication before system update.
- Update mruby-pax
    - Support bg image and custom font in Device::Pinpad.pin.
    - Implemented check of ms3des kcv,  ms3des stands for master session 3des.

### 5.57.0 - 2018-03-22

- Update main (1.71.0)
    - Restart if signature change.
    - Update posxml_parser (2.3.2).
        - Fix string_find return(-1) for empty substring.
        - Force string on interface_display_bitmap path var.

### 5.56.0 - 2018-03-22

- Update mruby-pax-network
    - Fix WIFI parameters string check to avoid null pointers when dealing with empty values.
- Update main (1.70.0)
    - Fix Notification reply.
    - Update da_funk (1.10.0)
        - Change Notification format removing repeated values.

### 5.55.0 - 2018-03-16

- Update mruby-pax-network
    - Only cache connected values when is a positive number.
- Update main (1.69.0)
    - Update posxml_parser (2.3.1)
        - Fix datetime_calculate sum/less calculation.
        - Fix datetime string expression.
        - Fix sum/less signals at datetime_calculate.

### 5.54.0 - 2018-03-16

- Update mruby-pax-network
    - Fix cache connected routine to return -3307 instead of -1012.

### 5.53.0 - 2018-03-15

- Update mruby-pax-network
    - Cache Network::connected? value.
- Update main (1.67.0)
    - Turn on display if any key is pressed.
- Update main (1.68.0)
    - Update posxml_parser (2.3.0).
        - Implement crypto_xor.

### 5.52.0 - 2018-03-02

- Update mruby-context
    - Implement rescue in start method instead of begin/end block.
    - Implement Device::System.teardown.
- Update mruby-pax
    - Fix Magnetic._read return.
    - Implement System::shutdown.
    - Replace System.shutdown by teardown.
    - Implement Printer.thread_kill.
- Update main (1.64.0)
    - Update posxml_parser (2.0.0)
        - Bug fix interface_menu function to expect “1.” And “1 “ entry numbers.
        - Support to send a pure xml code on PosxmlCompiler.compile.
        - Fix private method call at posxml_compiler scope.
        - Add posxml_compiler to ruby gem.
        - Release util_wait(miliseconds) if a key is pressed.
    - Update posxml_parser (2.1.0)
        - PosxmlCompiler refactoring VariableTypeError message.
        - PosxmlCompiler supports parameter validation.
    - Update posxml_parser (2.1.1)
        - Fix PosxmlCompiler en xsd to wait instruction.
        - Do not validate parameters if instruction does not support it.
- Update main (1.65.0)
    - Update posxml_parser (2.2.0)
        - Implement PosxmlParser::posxml_file_delete to remove file from cache and filesystem.
        - Implement extra empty check (“ “) for if parsing.
        - Remove cw_app_init.dat from cache and filesystem after use.
        - Remove unnecessary track call at card_read.
        - Check if file exist before delete at posxml_file_delete helper.
        - Remove cw_app_init.dat before mag and emv transaction update.
- Update main (1.66.0)
    - Update posxml_parser (2.2.1)
        - Fix getc parameter sent converting to integer.
        - Fix empty comparison when operator :!= during translation
    - Update da_funk (1.8.0)
        - Implement Device::System::shutdown.
        - Implement Device::Setting::heartbeat ParamsDat check.
    - Update da_funk (1.9.0)
        - Replace shutdown by teardown, more appropriated for application loop.

### 5.51.0 - 2018-02-16

- Update mruby-pax
    - Fix PAX class typo declaration at Magnetic.

### 5.50.0 - 2018-02-15

- Update mruby-pax
    - Implement beep after success magnetic read.
- Update main (1.63.0)
    - Update posxml_parser (1.3.1)
        - Fix PaymentChannel hierarchy call.

### 5.49.0 - 2018-02-09

- Remove memory profiling temporarily.
- Update mruby-pax
    - Implement Pinpad.key_ksn.
- Update mruby-context
    - Remove memory profiling temporarily.
- Update main (1.62.0)
    - Update da_funk (1.7.0)
        - Adopt “w” for FileDb and Transaction::Download write operation and improve IO time.
        - Implement ConnectionManagement class based on ParamsDat config.
        - Implement PaymentChannel via websocket.
    - Update da_funk (1.7.1)
        - Fix payment channel compilation.
    - Update posxml_parser (1.3.0)
        - Cache FileDb handle.
        - Adopt posxml mag configuration for card_read.
        - Implement custom translation to <if> statement to improve performance.

### 5.48.0 - 2018-02-05

- Update da_funk (1.6.0)
    - Remove Notification whitespace.
    - Implement Notification#reply.
    - Temporarily remove I18n require.
- Update main (1.61.0)
    - Send notification reply to notification.
    - Fix “AGUARDE” message during system update.
    - Fix system update message.
- Update mruby-pax
    - Fix touch limit check.

### 5.47.0 - 2018-01-26

- Update main (1.60.0)
    - Update funky-emv (0.16.2).
        - Return PPCOMP_ERRPIN when PAX::Pinpad::ERR_PED_GROUP_IDX_ERR during pin dukpt input.

### 5.46.0 - 2018-01-24

- Update mruby-qrcode - Necessary to not invert the generated qrcode.

### 5.45.0 - 2018-01-24

- Update mruby-pax
    - Add Pinpad::ERR_PED_GROUP_IDX_ERR = -3818 constant.
    - Fix Pinpad::key_kcv arguments.
    - Remove repeated Pinpad::load_key definition.
    - Add Pinpad::key_ksn.
- Update mruby-pax-network
    - Refact get_sim_card_id method too avoid system error on s920 terminals, for some reason the old strategy causes a memory leak.
    - Implement Network::configure
- Update main (1.58.0)
    - Update da_funk (1.4.4)
        - Fix Screen.add when column is missing
- Update main (1.59.0)
    - Update da_funk (1.5.0)
        - Implement Network::configure to split Network::init in two parts, configure for the definition of the interface, and init it self the system call.

### 5.44.0 - 2018-01-22

- Update main (1.57.0)
    - Bug fix timeout on APN menu.
    - Replace disconnect and power off functions for shutdown at communication menu.
    - Support to change terminal signature in about entry.
- Update mruby-pax-network
    - Force Wireless switch off during WIFI start.
    - Return fixnum value to troubleshooting wifi scan.
    - Close wifi during GPRS start.
    - Fix SIMID extraction.

### 5.43.0 - 2018-01-18

- Upate main (1.56.0)
    - Update funky-emv (0.16.1)
        - Fix get pin plain (offline) variable return the variable wasn’t being checked.
        - Return shared library value to PAX user cancel return.

### 5.42.0 - 2018-01-18

- Update main (1.55.0)
    - Update da_funk (1.4.3)
        - Refact automatic menu header reviewing limits.

### 5.41.0 - 2018-01-17

- Update main (1.54.0)
    - Fix countdown application configuration and implement generic parameter from params.dat.
    - Update cloudwalk (1.4.2).
    - Update da_funk (1.4.2).
        - Extract background pagination helper.
        - Refactoring menu helper to support footer, header and background customization.
    - Update posxml_parser (1.2.2).
        - Fix menu parse instruction removing empty entries.
        - Support type parameter between application execution.

### 5.40.0 - 2018-01-17

- Update main (1.53.0)
    - Add wait message before EMVTransaction start.
    - Update da_funk (1.4.1).
        - Fix Notification parse to make communication management works.
    - Update posxml_parser (1.2.1).
        - Fix parameter passing between applications.
        - Refactoring posxml menu parsing adopting the text given by options as key to be pressed.
        - Bugfix translation when use variables for filename on execute instruction.

### 5.39.0 - 2018-01-16

- Update main (1.51.0)
    - Update posxml_parser (1.1.0).
        - Update da_funk (1.3.1).
        - Bug fix posxml translation closing class translated.
    - Update da_funk(1.3.0).
        - Call String.to_f when reached Integer conversion limit
    - Update da_funk(1.3.1).
        - Fix String.integer? Method supporting Float.
- Update main (1.52.0)
    - Update I18n emv_enter_pin text.
    - Update cloudwalk (1.4.0).
    - Update da_funk (1.4.0).
        - Refactoring String.integer? And String.to_i adding more tests and support big numbers integer check.
        - Do no print menu entry if empty.
        - Implement Screen.add to print and update x and y.
        - Support to print background image on menu if title path exists.
    - Update funky-emv (0.16.0).
        - Only display emv remove card message if card still present.
        - Implement class responsible to perform Ui and add support to display image for pin entry and remove card.
    - Update funky-simplehttp (0.5.0).
        - Update da_funk (1.3.0).
        - Adopt da_funk gem structure.
    - Update posxml_parser (1.2.0).
        - Support background image on menu instructions.
        - Check string conversation to integer error on Variable class.
        - Refactoring string_replace instruction implementing a defensive code conversting to string for all variables.


### 5.38.0 - 2018-01-11

- Bug fix touch system error when terminal get the display size too many times a system error appears, to avoid it just adopt the display size from extern variables (ui.h).
- Update AerialMono.tar.gz (signed version).
- Update main (1.50.0)
    - Update da_funk (1.2.0)
        - Remove NotificatioTest, it’s outdated.
        - Fix DaFunk::Application test when receiving a label that wasn’t expected.
        - Replace crc16 of downloaded files strategy instead of read the entire file move the responsibility to decide the better approach, 1. Read the entire file, 2. Read each 10k. It’s necessary to avoid a system error on File.read greater than 900k.
        - Finish the excecution after custom test run to avoid rake to try run a task with the file name.
        - Check if file is bigger than 500k on Crypto::file_crc16_hex and if it is, calculate the crc in chuncks.
        - Implement Float.to_s with other bases 10, nil and others.
        - Refactoring String.to_i adopting Interger() instead of alias.
        - Add Float tests.
        - Fix Display Test covering MRuby 1.3.0 puts/print API.
        - Refactoring NotificationEventTest following the new implementation.

### 5.37.0 - 2018-01-10

- Update mruby-mtest.
- Update mruby-pax
    - Add beep for success touch event.
    - Adopt AerialMono.ttf as default font.
    - Always setup the font after a print. Because of the print/reset in every print, so it’s necessary to avoid terminal print in the old font.
- Update mruby-pax-network
    - Implement defensive communication check and avoid manual inputs.
- Update main (1.49.0)
    - Main::call receives Json to execute normal or admin menu.
    - Add menu option to delete only zip files.
    - Update posxml_parser (1.0.0).
        - Implement json parameter passing to ruby runtime exec.
        - Fix -2 check in input_format method.
        - Bug fix string_insert_at, old code from js.
    - Update cloudwalk (1.1.0).
    - Update da_funk (1.0.0).
        - Remove serfs interface and implement notification
interface via web socket.
        - Adopt ContextLog to store error on file download.
        - Implement force parameter to application, params dat and file download.
        - Unzip ruby application after download instead of execution call.
        - Move Application, Notification*, ParamsDat and Transaction from Device to Dafunk scope.
        - Remove transaction/emv.rb and refactor loads.
        - Remove Device:Helper.
        - Check if application file exists before return local crc.
        - Adopt custom exception for Application download.
        - Force unzip ruby application if file is the same.
        - Do not cache local crc on DaFunk::Application.
        - Adopt DaDunk::Application CRC check strategy in DaFunk::FileParameter
    - Update da_funk (1.1.0).
        - Rename Device::Printer#set_font to Device::Printer#font.
        - Fix #18 - Adopt Integer instead of Fixnum.
        - Check if adapter isn’t nil before check Crypto class.
        - Fix Float.to_s method generating implementing Alis for the old.
        - Refact String.to_i implementing alias for the old.
        - Refact number_to_currecy float test.
    - Update da_funk (1.1.1).
        - Update dependencies versions.

### 5.36.0 - 2018-01-04

- Touch screen handle became global and GetTouchScreen receive clear option to close handle.
- Implement ClearTouchScreen to remove TouchScreen handle.
- Update mruby-pax
	- Implement PAX::Touch .clear and .getxy_stream.
- Update main (1.48.0)
    - Implement menu entry to force app update with crc check (without cache) and force update all files.
    - Turn on Notification and Notification Callbacks.
    - Remove chars no ascii table at i18n.json.
    - Fix system update return line display.
    - PaymentChannel rescue SocketError and PolarSSL::SSL::Error.
    - Implement PaymentChannel::configured? to check error.
    - Replace Device:: for DaFunk:: on Transaction, ParamsDat and Notication.
    - Receive json on main.
    - Update cloudwalk_handshake (0.12.0).
        - Replace Device::Helper for DaFunk::Helper.
    - Update posxml_parser (0.31.0).
        - Bug fix add addition check on string_trim and avoid system error.
        - Fix PosxmlParserTest assertion on posxml2ruby process.
        - Refactoring interface_system_get_touchscreen_keyboard.
        - Replace Device::ParamsDat for DaFunk::ParamsDat.
        - Replace Device::Transaction for DaFunk::Transaction.
    - Update funky-emv (0.15.0).
        - Replace Device::ParamsDat for DaFunk::ParamsDat.
    - Update da_funk (1.0.0).
        - Remove serfs interface and implement notification interface via web socket.
        - Adopt ContextLog to store error on file download.
        - Implement force parameter to application, params dat and file download.
        - Unzip ruby application after download instead of execution call.
        - Move Application, Notification*, ParamsDat and Transaction from Device to Dafunk scope.
        - Remove transaction/emv.rb and refactor loads.
        - Remove Device:Helper.
        - Check if application file exists before return local crc.
        - Adopt custom exception for Application download.
        - Force unzip ruby application if file is the same.
        - Do not cache local crc on DaFunk::Application.
        - Adopt DaDunk::Application CRC check strategy in DaFunk::FileParameter

### 5.35.0 - 2017-12-07

- Update mruby-pax
	- Check if bitmap exists before display to avoid system error.

### 5.34.0 - 2017-12-07

- Update main (1.46.0)
    - Add support to backlight control configuration from parameters.
    - Add countdown menu entry when communication fail on fallback recovery.
    - Update da_funk (0.28.0).
        - Support to interrupt file download if KEY CANCEL pressed.

### 5.33.0 - 2017-12-04

- Update main (1.45.0).
    - Update da_funk (0.27.0).
        - Update rake dependency.

### 5.32.0 - 2017-12-04

- Update Gemfile.lock to update to posxml_parser (0.29.0).

### 5.31.0 - 2017-12-01

- Update main (1.42.0)
	- Check if params.dat exists before return connection_management flag.
- Update main (1.43.0)
    - Update posxml_parser (0.29.0)
        - Bug Fix key_main checking registration.
- Upate main (1.44.0)
    - Support to display merchant name.

### 5.30.0 - 2017-11-29

- Add new library to perform msgpack.
- Update mruby project url to mruby/mruby.git.
- Update mruby-pax
	- Add getxy to kernel.
	- Clear display after pin entry.
	- Fix getxy memory pointers return.
	- Implement custom font color on PIN input.
- Update main (1.40.0)
	- Check if cw_app_keys has “DEFINIR_APN” for manual entry too.
	- Update posxml_parser (0.27.0).
		- Check if application exists to create key_main trigger and if isn’t KEY_EXTRA1.
- Update main (1.41.0)
	- Update da_funk (0.25.0)
		- I18n, check if the current language was already configure to perform the merge options.
		- Add Support tests.
		- Implement String#snakecase.
	- Update da_funk (0.26.0)
		- Change default serf notification creation timeout to 180 seconds.
		- Support new MessagePack syntax.
	- Update funky-emv (0.14.0)
		- Implement custom RGB for pins input on PAX.
	- Update posxml_parser (0.28.0).
		- Implement XsdParser#find to get instruction by name.
		- Check if Kernel#getxy is defined to call in touch instructions.
		- Implement the first version of Xml translation to ruby.
		- Add support to load and execute ruby translation code.
		- At util_exit rise exit to perform exit on translation.
		- Update Gemfile.lock.

### 5.29.0 - 2017-11-08

- Update main (1.39.0)
    - Update ext/float.rb to compilation.

### 5.28.0 - 2017-11-08

- Touch Screen second approach initial implementation.
- Finish new touch screen abstraction.
- Update mruby-io to master HEAD.
- Update mruby (1.3.0) from mruby/mruby (without bignulls support).
- Remove mruby gems mruby-bignum, mruby-simple-random mruby-mock and mruby-msgpack.
- Update main (1.37.0)
	- Force close payment channel after communication management fail.
- Update main (1.38.0)
	- Update posxml_parser (0.26.0)
		- Fix card_get_variable timeout.
		- Implemented interface_system_get_touchscreen and interface_system_get_touchscreen_keyboard.
	- Update cloudwalk_handshake (0.11.0).
		- Change License to MIT.
		- Check if web socket exists to close or check response.
	- Update da_funk (0.23.0)
		- Implement String#to_big.
		- Implement custom Float#to_s(16).
- Update mruby-pax-network
	- Make GPRS.disconnect return Fixnum value.
	- Turn wifi connect non-blocking.
- Update mruby-socket
	- TCPSocket#initialize temporary fix to make it work with mruby 1.3.0, check https://github.com/iij/mruby-socket/issues/36
- Update mruby-pax
	- Set persist.sys.timezone.tz in hwclock.
	- Touch Screen refactoring.
	- Refactoring printer thread:
		- Add periodically buffer check before print.
		- Add timeout to loop.

### 5.27.0 - 2017-11-04

- Update mruby-pax-network
    - Refactoring GPRS and WIFI power off releasing resource.
- Update main (1.36.0)
    - Update da_funk (0.22.0)
        - Bug fix Device::Network.attach_timeout when dealing with wifi.
        - Always shutdown interface after communication error/

### 5.26.0 - 2017-11-03

- Update mruby-pax
	- Add “@“ char to keyboard special chars.
	- Refactoring printer thread:
		- Add periodically buffer check before print.
		- Add timeout to loop.
- Update main (1.35.0)
	- Check connection before execute mag or emv transaction.
	- Bug fix the primary connection try logic after reboot.
	- Add all flags to README.
	- Update posxml_parser (0.24.0).
		- Fix tag ttlnbofpmts generation on iso20022.
	- Update posxml_parser (0.25.0).
		- Check connection before execute reversal.
	- Update da_funk (0.20.0)
		- Adopt connection_management 1 as default.
	- Update da_funk (0.21.0)
		- Implement custom Device::Setting.attach_gprs_timeout.
		- Adopt custom GPRS timeout on Network.attach.
		- Adopt temporary processing returns at Device::Network.attach.

### 5.25.0 - 2017-10-30

- Update main (1.33.0)
	- Update funky-emv (0.13.0)
		- Check ICC RSP6985 at process transaction on pax flow.
- Update mruby-pax
	- Add “!” To keyboard configuration.
	- Refactoring all Printer’s print methods to not print in the moment of the call, but instead add the text to a buffer. And added a method specific for print the current buffer.
	- Add support to print in a separated thread.
	- Update Print open removing unnecessary calls.

### 5.24.0 - 2017-10-23

- Update main (1.32.0)
    - Update funky-emv (0.12.0)
        - Refactoring selection menu to avoid the same label.

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
