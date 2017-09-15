# RobotRock

RobotRock is the Ruby Walk Framework for PAX.

## Setup

- Clone on `/shared/pax/robot_rock` path.

- Initialize and update submodules:

```
git submodule update --init --recursive
# If '--rescursive' not work check mrbgems/mruby-polarssl and mrbgems/mruby-qrcode submodules
```

- Install C/C++ Express, [check link here.](https://www.visualstudio.com/pt-br/products/visual-studio-express-vs.aspx)

- Insert the terminal on the VM and check driver recognation, if you have problems, check `lib/sdk/driver*`.

- On repository path, at host machine terminal, install gems with `bundle install`.

- On `Vagrant ssh` setup bundler, execute `rake pax:bundle_install`.


## Compiling and Deploying

1. Compile mruby, generating libmruby.a, on `Visual Studio Prompt Command` using `rake pax:mruby:build`.

2. Compile ruby files, generating mrb files and resources using `rake pax:mrbc`

3. Compile PAX project, generating the final package, on `Vagrant ssh` using `rake pax:rebuild`

4. Upload the package, on `Vagrant ssh` using `rake pax:upload`

    ** * To change com configuration (default COM3) check lib/tasks/pax.rake **


## Usage

Rake tasks availables on Vagrant:

    rake clean               # Remove any temporary products
    rake clobber             # Remove any generated files
    rake pax:bundle_install  # Install gems needed by main project
    rake pax:clean           # Clobber/Clean PAX
    rake pax:compile         # Compile PAX
    rake pax:deploy          # Rebuild PAX
    rake pax:mrb_load        # Compile MRB, generate package and upload
    rake pax:mrbc            # Generate mrb file
    rake pax:rebuild         # Rebuild PAX
    rake pax:setup           # Setup PAX ENV
    rake pax:test            # Test Platform Main
    rake pax:upload          # Upload
	
Rake tasks availables on Visual Studio Commnad Prompt

    rake pax:mruby:build     # Build
    rake pax:mruby:clean     # Clean MRuby
    rake pax:mruby:compile   # Compile MRuby and generate libmruby.a
    rake pax:mruby:env       # Setup env
    rake pax:mruby:rebuild   # Rebuild

## Linking libraries

#### Path

1. Configure local path library - Add path lib with -L, lib/tasks/pax.rake:161: `-L”lib/emv”`, example: `-L\"#{File.join(PAX_LIB_ROOT, "emv")}\”`
2. Configure remote path library(terminal) - Add library path considering the internal terminal path, this, in specific, already is confgured, but is good to metion, check it lib/tasks/pax.rake:161: `-Wl,-rpath=./lib`.

#### Library file

After configured the path we need to configure the files locally and remotally.

1. Local file - It is necessary to add the file name, without extension and prefix "lib" with `-l`, on `lib/tasks/pax.rake:161`, `-l<nome lib sem extensão>`, example: `-lEMVS2FMProlin_v506` (We have this file locally `lib/sdk/emv/libEMVS2FMProlin_v506.so`)
2. Remote file - It is necessary to create a symbol link of the file on `out/lib/lib`, because this directory will be uploaded to terminal. Remember to create this symbol link using relative path, example:

```
$ pwd
/Users/thiagoscalone/projects/plano_be/walk/pax/robot_rock
$ cd out/lib/
$ ln -s ../../lib/sdk/emv/libEMVS2FMProlin_v506.so ./
```

You should **NOT** create from the project root path:

```
$ pwd
/Users/thiagoscalone/projects/plano_be/walk/pax/robot_rock
$ ln -s lib/sdk/emv/libEMVS2FMProlin_v506.so ./out/lib
```

## Release and Bump version

- Change version number on the files `mrblib/version.rb` and `out/appinfo`.
- Generate mrb files `rake pax:mrbc SIGNATURE=production`
- Generate aip `rake pax:rebuild SIGNATURE=production`


## Certificates

- You can find all certificates at our Dropbox account [here](https://www.dropbox.com/home/Walk/Pos/PAX/certificates)


## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Added some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request