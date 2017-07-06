require 'fileutils'
require 'rake/clean'

MRUBY_PAX_ROOT = ENV["MRUBY_PAX_ROOT"] || File.join(File.dirname(File.expand_path(__FILE__)), "..", "..")
PAX_LIB_ROOT   = File.join(MRUBY_PAX_ROOT, "lib", "sdk")
MRUBY_LIB      = File.join(MRUBY_PAX_ROOT, "lib", "mruby")
DA_FUNK_LIB    = File.join(MRUBY_PAX_ROOT, "lib", "da_funk")
MAIN_LIB       = File.join(MRUBY_PAX_ROOT, "lib", "main")
MRUBY_PAX_MGEM = File.join(MRUBY_PAX_ROOT, "mrbgems")
MRUBY_PAX_INC  = File.join(MRUBY_PAX_ROOT, "src")
GCC_PAX_BIN    = File.join(PAX_LIB_ROOT, "sdk", "toolchains", "arm-4.4.1", "bin", "arm-none-linux-gnueabi-gcc")
AR_PAX_BIN     = File.join(PAX_LIB_ROOT, "sdk", "toolchains", "arm-4.4.1", "bin", "arm-none-linux-gnueabi-ar")
LOCINCLUDE     = [MRUBY_PAX_INC, File.join(MRUBY_LIB, "include"), File.join(PAX_LIB_ROOT, "sdk", "platforms", "paxngfp_201205", "include"), File.join(PAX_LIB_ROOT, "sdk", "platforms", "paxngfp_201205", "include", "freetype"), File.join(PAX_LIB_ROOT, "sdk", "toolchains", "arm-4.4.1", "arm-none-linux-gnueabi", "libc", "usr", "include"), File.join(PAX_LIB_ROOT, "emv")]
SIGNATURE      = ENV["SIGNATURE"] == "production" ? "production" : "mockup"

SH_EXE         = "C:\\cygwin\\bin\\sh.exe"

require File.join(MRUBY_PAX_ROOT, "mrblib", "version.rb")

if RUBY_PLATFORM == "i386-mingw32"
  ENV["MRBC"]  = File.join(MRUBY_LIB, "bin", "mrbc.exe")
else
  ENV["MRBC"]  ||= "env mrbc"
end

if ENV["MRUBY_CONFIG"]
  MRuby::Toolchain.new(:visualcpp) do |conf|
    [conf.cc].each do |cc|
      cc.command = ENV['CC'] || 'cl.exe'
      # C4013: implicit function declaration
      cc.flags = [ENV['CFLAGS'] || %w(/c /nologo /W3 /we4013 /Zi /MD /O2 /D_CRT_SECURE_NO_WARNINGS)]
      cc.defines = %w(DISABLE_GEMS MRB_STACK_EXTEND_DOUBLING ENABLE_DEBUG)
      cc.option_include_path = '/I%s'
      cc.option_define = '/D%s'
      cc.compile_options = "%{flags} /Fo%{outfile} %{infile}"
    end

    [conf.cxx].each do |cxx|
      cxx.command = ENV['CXX'] || 'cl.exe'
      cxx.flags = [ENV['CXXFLAGS'] || ENV['CFLAGS'] || %w(/c /nologo /W3 /Zi /MD /O2 /EHsc /D_CRT_SECURE_NO_WARNINGS)]
      cxx.defines = %w(DISABLE_GEMS MRB_STACK_EXTEND_DOUBLING ENABLE_DEBUG)
      cxx.option_include_path = '/I%s'
      cxx.option_define = '/D%s'
      cxx.compile_options = "%{flags} /Fo%{outfile} %{infile}"
    end

    conf.linker do |linker|
      linker.command = ENV['LD'] || 'link.exe'
      linker.flags = [ENV['LDFLAGS'] || %w(/NOLOGO /DEBUG /INCREMENTAL:NO /OPT:ICF /OPT:REF)]
      linker.libraries = %w()
      linker.library_paths = %w()
      linker.option_library = '%s.lib'
      linker.option_library_path = '/LIBPATH:%s'
      linker.link_options = "%{flags} /OUT:%{outfile} %{objs} %{flags_before_libraries} %{libs} %{flags_after_libraries}"
    end

    conf.archiver do |archiver|
      archiver.command = ENV['AR'] || 'lib.exe'
      archiver.archive_options = '/nologo /OUT:%{outfile} %{objs}'
    end

    conf.yacc do |yacc|
      yacc.command = ENV['YACC'] || 'bison.exe'
      yacc.compile_options = '-o %{outfile} %{infile}'
    end

    conf.gperf do |gperf|
      gperf.command = 'gperf.exe'
      gperf.compile_options = '-L ANSI-C -C -p -j1 -i 1 -g -o -t -N mrb_reserved_word -k"1,3,$" %{infile} > %{outfile}'
    end

    conf.exts do |exts|
      exts.object = '.obj'
      exts.executable = '.exe'
      exts.library = '.lib'
    end

    conf.file_separator = '\\'
  end

  MRuby::Toolchain.new(:pax) do |conf|
    conf.define_singleton_method(:host_target) { "" }

    [conf.cc, conf.cxx, conf.objc, conf.asm].each do |cc|
      cc.command = GCC_PAX_BIN
      cc.flags = [%w(-O0 -g2 -Wall -funwind-tables -std=gnu99)]
      cc.include_paths = ["#{MRUBY_ROOT}/include"].concat(LOCINCLUDE)
      cc.defines = %w(ENABLE_DEBUG MRB_STACK_EXTEND_DOUBLING SHA256_DIGEST_LENGTH=32 SHA512_DIGEST_LENGTH=64)
      cc.option_include_path = '-I%s'
      cc.option_define = '-D%s'
      cc.compile_options = '%{flags} -c %{infile} -o %{outfile} '
    end

    conf.archiver do |archiver|
      archiver.command = AR_PAX_BIN
      archiver.archive_options = 'r %{outfile} %{objs}'
    end

    conf.exts do |exts|
      exts.object = '.o'
      exts.executable = '.out'
      exts.library = '.a'
    end

    conf.file_separator = '\\'
  end

  MRuby::Build.new do |conf|
    # load specific toolchain settings
    toolchain :visualcpp
    conf.cc.defines = %w(ENABLE_DEBUG)
    conf.bins = %w(mrbc)
  end

  MRuby::CrossBuild.new('pax') do |conf|
    #TODO builddir
    toolchain :pax

    conf.cc.defines = %w(PAX ENABLE_DEBUG)
    conf.cc.include_paths << MRUBY_PAX_INC
    conf.bins = []
    conf.gembox File.join(MRUBY_PAX_MGEM, "pax")

    conf.file_separator = '\\'
  end
end

namespace :pax do
  namespace :mruby do
    build_args = ARGV[1..-1]
    desc "Compile MRuby and generate libmruby.a"
    task :compile => :setup do
      exit sh "rake #{build_args.join(' ')}"
    end

    desc "Clean MRuby"
    task :clean => :env do
      exit sh "rake clean #{build_args.join(' ')}"
    end

    desc "Setup env"
    task :env do
      FileUtils.cd MRUBY_LIB
      ENV["MRUBY_CONFIG"] = File.expand_path(__FILE__)
    end

    desc "Build"
    task :build => :env  do
      sh "rake #{build_args.join(' ')}"
      exit
    end

    desc "Rebuild"
    task :rebuild => :env  do
      sh "rake clean #{build_args.join(' ')}"
      sh "rake #{build_args.join(' ')}"
      exit
    end
  end

  desc "Setup PAX ENV"
  task :setup do
    ::CLEAN.include "out/obj/*.o"
    ::CLOBBER.include "out/obj/*.bin", "out/obj/*.nostrip"
  end

  # TODO Remove or not
  rule '.o' => ["%{out/obj,src}X.c"] do |t|
    sh "#{GCC_PAX_BIN} -O0 -g2 -Wall -funwind-tables -I#{LOCINCLUDE.join(" -I")} #{t.source} -c -o #{t.name}"
  end

  SRC = FileList["src/*.c"]
  BIN = SRC.pathmap("%{src,out/obj}X.o")

  task :link => BIN do
    #CTLS link
    #sh "#{File.join(PAX_LIB_ROOT, "sdk", "toolchains", "arm-4.4.1", "bin", "arm-none-linux-gnueabi-gcc")} -o\"app.nostrip\" #{BIN.join(" ")} -L\"#{File.join(PAX_LIB_ROOT, "emv")}\" -L\"#{File.join(PAX_LIB_ROOT, "sdk", "platforms", "paxngfp_201205", "lib")}\" -losal -Wl,-rpath=//opt/lib -Wl,-rpath=./lib -Wl,-rpath-link,\"#{File.join(PAX_LIB_ROOT, "sdk", "platforms", "paxngfp_201205", "lib")}\" -lm -lcrypto -lfreetype -lpng -lpthread -lts -lxui #{File.join(MRUBY_LIB, "build", "pax", "lib", "libmruby.a")} -lEMVS2FMProlin_v506 -lClEntryS2FMProlin_ccv_v502 -lClEntryS2FMProlin_v502 -lClMCS2FMProlin_ccv_v402 -lClWaveS2FMProlin_v303"
    sh "#{File.join(PAX_LIB_ROOT, "sdk", "toolchains", "arm-4.4.1", "bin", "arm-none-linux-gnueabi-gcc")} -o\"app.nostrip\" #{BIN.join(" ")} -L\"#{File.join(PAX_LIB_ROOT, "sdk", "platforms", "paxngfp_201205", "lib")}\" -losal -Wl,-rpath=//opt/lib -Wl,-rpath=./lib -Wl,-rpath-link,\"#{File.join(PAX_LIB_ROOT, "sdk", "platforms", "paxngfp_201205", "lib")}\" -lm -lMID -lcrypto -lD_EMV_LIB_v602_01 -liniparser -lfreetype -lpng -lpthread -lts -lxui #{File.join(MRUBY_LIB, "build", "pax", "lib", "libmruby.a")} -L\"#{File.join(PAX_LIB_ROOT, "emv")}\""
    FileUtils.mv "app.nostrip", "out/app.nostrip"
    FileUtils.cd "#{File.join(MRUBY_PAX_ROOT, "out")}"
    sh "#{File.join(PAX_LIB_ROOT, "sdk", "toolchains", "arm-4.4.1", "bin", "arm-none-linux-gnueabi-strip")} -g app.nostrip -o\"RobotRock\""
  end

  task :generate_aip do
    File.open(File.join(MRUBY_PAX_ROOT, "out", "shared", "device.sig"), "wb") {|f| f.write("signer=#{SIGNATURE}") }
    FileUtils.cd "#{File.join(MRUBY_PAX_ROOT, "out")}"
    sh "#{File.join(PAX_LIB_ROOT, "sdk", "tools", "genaip")} -I pkginfo -o pkg/RobotRock.aip"
  end

  desc "Install gems needed by main project"
  task :bundle_install do
    FileUtils.cd MAIN_LIB
    sh "bundle install"
  end

  desc "Generate mrb file"
  task :mrbc do
    # Clean
    mrb = File.join(MRUBY_PAX_ROOT, "out", "main")
    FileUtils.rm_rf(mrb)
    FileUtils.mkdir_p(mrb)

    shared = File.join(MRUBY_PAX_ROOT, "out", "shared")
    FileUtils.rm_rf(shared)
    FileUtils.mkdir_p(shared)

    # Main
    FileUtils.cd MAIN_LIB
    sh "bundle exec rake"
    FileUtils.cd MRUBY_PAX_ROOT
    FileList[File.join(MAIN_LIB, "out", "main", "*")].each do |file|
      FileUtils.mv(file, mrb)
    end
    FileList[File.join(MAIN_LIB, "out", "shared", "*")].each do |file|
      FileUtils.mv(file, shared)
    end

    # DaFunk
    FileUtils.cd DA_FUNK_LIB
    sh "bundle exec rake"
    FileUtils.cd MRUBY_PAX_ROOT
    funk     = File.join(DA_FUNK_LIB, "out", "da_funk.mrb")
    funk_mrb = File.join(mrb, "da_funk.mrb")
    FileUtils.cp(funk, funk_mrb)

    # PAX
    pax_out = File.join(mrb, "pax.mrb")
    pax_rb = [
      File.join(MRUBY_PAX_ROOT, "mrblib", "version.rb"),
      File.join(MRUBY_PAX_ROOT, "mrblib", "init.rb"),
      File.join(MRUBY_PAX_ROOT, "mrblib", "device.rb"),
      File.join(MRUBY_PAX_ROOT, "mrblib", "#{SIGNATURE}.rb")
    ]

    sh "#{ENV['MRBC']} -g -o #{pax_out} #{pax_rb.join(" ")}"
  end

  desc "Clobber/Clean PAX"
  task :clean => [:setup] do
    # Allow task to invoke again
    Rake::Task['clean'].reenable
    Rake::Task['clobber'].reenable

    Rake::Task['clobber'].invoke
  end

  desc "Upload"
  task :upload do
    xcb = File.join(PAX_LIB_ROOT, "TermAssist", "tools", "xcb.exe")
    sh "#{xcb} connect com:com3"
    sh "#{xcb} installer aip #{File.join(MRUBY_PAX_ROOT, "out", "pkg", "RobotRock.aip")}"
    sh "#{xcb} disconnect com:com3"
  end

  desc "Test Platform Main"
  task :test => :mrbc do
    test_path = File.join(MRUBY_PAX_ROOT, "test")
    FileUtils.rm_rf(File.join(test_path, "execution"))
    FileUtils.mkdir_p(File.join(test_path, "execution", "main"))
    FileUtils.cp(File.join(test_path, "main.rb"), File.join(test_path, "execution", "main.rb"))
    FileUtils.cd File.join(test_path, "execution")

    sh "mruby ./main.rb"
  end

  desc "Last compilation package generation"
  task :package do
    require "archive/zip"

    pkg_path = File.join(MRUBY_PAX_ROOT, "out", "pkg", PAX.version)
    git_hash = `git rev-parse --short HEAD`.chomp
    sign     = File.read(File.join(MRUBY_PAX_ROOT, "out", "shared", "device.sig")).split("=").last
    name     = "cloudwalk_framework-prolin-#{PAX.version.gsub(".", "_")}-#{sign}-#{git_hash}.zip"
    zip      = File.join(MRUBY_PAX_ROOT, "out", "pkg", name)

    FileUtils.rm_rf(pkg_path)
    FileUtils.mkdir_p(File.join(pkg_path, "driver"))
    FileUtils.cp_r(File.join(PAX_LIB_ROOT, "TermAssist"), pkg_path)
    FileUtils.cp(File.join(MRUBY_PAX_ROOT, "out", "pkg", "RobotRock.aip"), File.join(pkg_path, "cloudwalk_framework.aip"))
    FileUtils.cp(File.join(PAX_LIB_ROOT, "driver", "posvcom_2.5.0.0.rar"), File.join(pkg_path, "driver"))

    Archive::Zip.archive(zip, pkg_path)
  end

  desc "Compile PAX"
  task :compile => [:setup, :link]

  desc "Rebuild PAX"
  task :rebuild => [:clean, :compile, :generate_aip]

  desc "Rebuild PAX"
  task :deploy => [:rebuild, :upload]

  desc "Compile MRB, generate package and upload"
  task :mrb_load => [:mrbc, :generate_aip, :upload]
end

