require 'fileutils'
require 'rake/clean'

MRUBY_PAX_ROOT = ENV["MRUBY_PAX_ROOT"] || File.join(File.dirname(File.expand_path(__FILE__)), "..", "..")
PAX_LIB_ROOT   = File.join(MRUBY_PAX_ROOT, "lib", "sdk")
MRUBY_LIB      = File.join(MRUBY_PAX_ROOT, "lib", "mruby")
DA_FUNK_LIB    = File.join(MRUBY_PAX_ROOT, "lib", "da_funk")
MRUBY_PAX_MGEM = File.join(MRUBY_PAX_ROOT, "mrbgems")
MRUBY_PAX_INC  = File.join(MRUBY_PAX_ROOT, "src")
GCC_PAX_BIN    = File.join(PAX_LIB_ROOT, "sdk", "toolchains", "arm-4.4.1", "bin", "arm-none-linux-gnueabi-gcc")
AR_PAX_BIN    = File.join(PAX_LIB_ROOT, "sdk", "toolchains", "arm-4.4.1", "bin", "arm-none-linux-gnueabi-ar")
LOCINCLUDE     = [MRUBY_PAX_INC, File.join(MRUBY_LIB, "include"), File.join(PAX_LIB_ROOT, "sdk", "platforms", "paxngfp_201205", "include"), File.join(PAX_LIB_ROOT, "sdk", "platforms", "paxngfp_201205", "include", "freetype"), File.join(PAX_LIB_ROOT, "sdk", "toolchains", "arm-4.4.1", "arm-none-linux-gnueabi", "libc", "usr", "include")]

SH_EXE         = "C:\\cygwin\\bin\\sh.exe"

require File.join(MRUBY_PAX_ROOT, "lib", "version.rb")

ENV["MRBC"]    = File.join(MRUBY_LIB, "bin", "mrbc.exe")

if ENV["MRUBY_CONFIG"]
  MRuby::Toolchain.new(:visualcpp) do |conf|
    [conf.cc, conf.cxx].each do |cc|
      cc.command = 'cl.exe'
      cc.flags = [%w(/c /nologo /W3 /D_DEBUG /MDd /Zi /Od /RTC1 /DHAVE_STRING_H /DNO_GETTIMEOFDAY /D_CRT_SECURE_NO_WARNINGS)]
      cc.include_paths = ["#{MRUBY_ROOT}/include", "Z:\\pax\\robot_rock\\lib\\sdk\\include"]
      cc.defines = %w(DISABLE_GEMS)
      cc.option_include_path = '/I%s'
      cc.option_define = '/D%s'
      cc.compile_options = "%{flags} /Fo%{outfile} %{infile}"
    end

    conf.linker do |linker|
      linker.command = 'link.exe'
      linker.flags = [%w(/nologo)]
      linker.libraries = %w()
      linker.libraries = %w()
      linker.library_paths = %w()
      linker.option_library = '%s.lib'
      linker.option_library_path = '/LIBPATH:%s'
      linker.link_options = "%{flags} /OUT:%{outfile} %{objs} %{flags_before_libraries} %{libs} %{flags_after_libraries}"
    end

    conf.archiver do |archiver|
      archiver.command = 'lib.exe'
      archiver.archive_options = '/nologo /OUT:%{outfile} %{objs}'
    end

    conf.yacc do |yacc|
      yacc.command = 'bison.exe'
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
    [conf.cc, conf.cxx, conf.objc, conf.asm].each do |cc|
      cc.command = GCC_PAX_BIN
      cc.flags = [%w(-O0 -g2 -Wall -funwind-tables)]
      cc.include_paths = ["#{MRUBY_ROOT}/include"].concat(LOCINCLUDE)
      cc.defines = %w()
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
    conf.bins = %w(mrbc)
  end

  MRuby::CrossBuild.new('pax') do |conf|
    #TODO builddir
    toolchain :pax

    conf.cc.defines = %w(PAX EXIT_FAILURE)
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
    sh "#{File.join(PAX_LIB_ROOT, "sdk", "toolchains", "arm-4.4.1", "bin", "arm-none-linux-gnueabi-gcc")} -o\"app.nostrip\" #{BIN.join(" ")} -L\"#{File.join(PAX_LIB_ROOT, "sdk", "platforms", "paxngfp_201205", "lib")}\" -losal -Wl,-rpath=//opt/lib -Wl,-rpath=./lib -Wl,-rpath-link,\"#{File.join(PAX_LIB_ROOT, "sdk", "platforms", "paxngfp_201205", "lib")}\" -lm -lcrypto -lfreetype -lpng -lpthread -lts -lxui #{File.join(MRUBY_LIB, "build", "pax", "lib", "libmruby.a")}"
    FileUtils.mv "app.nostrip", "out/app.nostrip"
    FileUtils.cd "#{File.join(MRUBY_PAX_ROOT, "out")}"
    sh "#{File.join(PAX_LIB_ROOT, "sdk", "toolchains", "arm-4.4.1", "bin", "arm-none-linux-gnueabi-strip")} -g app.nostrip -o\"RobotRock\""
  end

  task :generate_aip do
    FileUtils.cd "#{File.join(MRUBY_PAX_ROOT, "out")}"
    sh "#{File.join(PAX_LIB_ROOT, "sdk", "tools", "genaip")} -I pkginfo -o pkg/RobotRock.aip"
  end

  desc "Generate mrb file"
  task :mrbc do
    # Clean
    mrb = File.join(MRUBY_PAX_ROOT, "out", "mrb")
    FileUtils.rm_rf(mrb)
    FileUtils.mkdir_p(mrb)

    # DaFunk
    FileUtils.cd DA_FUNK_LIB
    sh "rake compile"
    FileUtils.cd MRUBY_PAX_ROOT
    funk     = File.join(DA_FUNK_LIB, "out", "da_funk.mrb")
    funk_mrb = File.join(mrb, "da_funk.mrb")
    FileUtils.mv(funk, funk_mrb)

    # PAX
    pax_out = File.join(mrb, "pax.mrb")
    pax_rb  = Dir[File.join(MRUBY_PAX_ROOT, "mrblib", "*.rb")]
    sh "#{ENV['MRBC']} -o #{pax_out} #{pax_rb.join(" ")}"

    sh "#{ENV['MRBC']} -o #{File.join(mrb, "main.mrb")} #{File.join(MRUBY_PAX_ROOT, "main.rb")}"
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

  desc "Compile PAX"
  task :compile => [:setup, :link]

  desc "Rebuild PAX"
  task :rebuild => [:clean, :compile, :generate_aip]

  desc "Rebuild PAX"
  task :deploy => [:rebuild, :upload]

  desc "Compile MRB, generate package and upload"
  task :mrb_load => [:mrbc, :generate_aip, :upload]
end
