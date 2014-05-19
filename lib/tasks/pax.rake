require 'fileutils'
require 'rake/clean'

MRUBY_PAX_ROOT = ENV["MRUBY_PAX_ROOT"] || File.join(File.dirname(File.expand_path(__FILE__)), "..", "..")
MUSL_ROOT      = File.join(MRUBY_PAX_ROOT, "lib", "musl")
PAX_LIB_ROOT   = File.join(MRUBY_PAX_ROOT, "lib", "sdk")
MRUBY_LIB      = File.join(MRUBY_PAX_ROOT, "lib", "mruby")
MRUBY_PAX_MGEM = File.join(MRUBY_PAX_ROOT, "mrbgems")
PAX_LIB_INC    = File.join(PAX_LIB_ROOT, "include")
MRUBY_PAX_INC  = File.join(MRUBY_PAX_ROOT, "src")
GCC_PAX_PATH   = File.join(PAX_LIB_ROOT, "build", "gcc-sde")
GCC_PAX_BIN    = File.join(GCC_PAX_PATH, "bin")
GCC_PAX_LIB    = File.join(GCC_PAX_PATH, "lib")
LOCINCLUDE     = [MRUBY_PAX_INC, PAX_LIB_INC, File.join(MRUBY_LIB, "include"), File.join(MUSL_ROOT, "include")]
DEV_KIT_MAKE   = "C:\\Ruby193\\devkit\\bin\\make"
SH_EXE         = "C:\\cygwin\\bin\\sh.exe"

require File.join(MRUBY_PAX_ROOT, "lib", "version.rb")

# DEBUG soft-float
#ENV["CFLAGS"]  = "-mtune=4ksd -mips32r2 -c -D_32_ -EL -O1 -ffixed-14 -ffixed-15 -G0 -fomit-frame-pointer -Wimplicit -Wformat -ffreestanding -mlong-calls -gdwarf-2 -msoft-float"
ENV["CFLAGS"]  = "-mtune=4ksd -mips32r2 -c -D_32_ -EL -O1 -ffixed-14 -ffixed-15 -G0 -fomit-frame-pointer -Wimplicit -Wformat -ffreestanding -mlong-calls -gdwarf-2"
ENV["LOCINC"]  = "-I\"#{LOCINCLUDE.join("\" -I\"")}\""
ENV["GCC"]     = "#{File.join(GCC_PAX_BIN, "sde-gcc.exe")} #{ENV['CFLAGS']} #{ENV["LOCINC"]}"
ENV['LD']      = File.join(GCC_PAX_BIN, "sde-ld.exe")
ENV["AR"]      = File.join(GCC_PAX_BIN, "sde-ar.exe")
ENV["GCCDIR"]  = GCC_PAX_PATH
ENV["GCCBIN"]  = GCC_PAX_BIN

if ENV["MRUBY_CONFIG"]
  MRuby::Toolchain.new(:visualcpp) do |conf|
    [conf.cc, conf.cxx].each do |cc|
      cc.command = 'cl.exe'
      cc.flags = [%w(/c /nologo /W3 /D_DEBUG /MDd /Zi /Od /RTC1 /DHAVE_STRING_H /DNO_GETTIMEOFDAY /D_CRT_SECURE_NO_WARNINGS)]
      cc.include_paths = ["#{MRUBY_ROOT}/include", "Z:\\pax\\mruby-pax\\lib\\sdk\\include"]
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
    ENV["PATH"]    = "#{ENV["PATH"]};C:\\WINDOWS;C:\\WINDOWS\\system32;#{GCC_PAX_BIN}"
    #ENV["NAME"]    = "robot_rock"
    ENV["LOCOBJ"]  = File.join(MRUBY_LIB, "build", "pax", "src")

    [conf.cc, conf.cxx, conf.objc, conf.asm].each do |cc|
      cc.command = File.join(GCC_PAX_BIN, "sde-gcc.exe")
      cc.flags = [%w(-mtune=4ksd -mips32r2 -c -EL -O1 -ffixed-14 -ffixed-15 -G0 -fomit-frame-pointer -Wimplicit -Wformat -ffreestanding -mlong-calls -gdwarf-2 -msoft-float)]
      cc.include_paths = ["#{MRUBY_ROOT}/include"].concat(LOCINCLUDE)
      cc.defines = %w()
      cc.option_include_path = '-I%s'
      cc.option_define = '-D%s'
      cc.compile_options = '%{flags} -c %{infile} -o %{outfile} '
    end

    conf.archiver do |archiver|
      archiver.command = ENV["AR"] 
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

    #enable_debug
    conf.bins = %w(mrbc)

    # include the default GEMs
    conf.gembox File.join(MRUBY_PAX_MGEM, "pax")
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
  namespace :musl do
    desc "Setup musl ENV"
    task :setup do
      ENV["LOCOBJ"]        = File.join(MUSL_ROOT, "obj")
      ENV['CROSS_COMPILE'] = File.join(GCC_PAX_BIN, "sde-")
    end

    desc "Compile Musl libc"
    task :compile => :setup do
      FileUtils.cd MUSL_ROOT
      sh "#{SH_EXE} configure --target=mips"
      FileUtils.rm_rf("include/bits")
      FileUtils.cp_r("arch/mips/bits", "include/")
      sh "#{DEV_KIT_MAKE}"
      exit
    end

    desc "Clean Musl libc"
    task :clean => :setup do
      FileUtils.cd MUSL_ROOT
      FileUtils.rm_rf("include/bits")
      sh "#{DEV_KIT_MAKE} clean"
      exit
    end
  end

  namespace :mruby do
    build_args = ARGV[1..-1]
    desc "Compile MRuby and generate libmruby.a"
    task :compile => :setup do
      exit sh "rake #{build_args.join(' ')}"
    end

    desc "Clean MRuby"
    task :clean => :setup do
      exit sh "rake clean #{build_args.join(' ')}"
    end

    desc "Setup"
    task :setup do
      FileUtils.cd MRUBY_LIB
      ENV["MRUBY_CONFIG"] = File.expand_path(__FILE__)
    end
  end

  desc "Setup PAX ENV"
  task :setup do
    ENV["NAME"]      = "robot_rock"
    ENV["VERSION"]   = PAX.version
    ENV['POSLIB']    = "d210api"
    ENV["GCCLIB"]    = GCC_PAX_LIB
    ENV["POSLIB"]    = File.join(ENV["POSLIBDIR"], "d210api")
    ENV["ASM"]       = "#{File.join(GCC_PAX_BIN, "sde-gcc.exe")} -xassembler-with-cpp -mtune=4ksd -mips32r2 -msmartmips -c -D_32_ -D_ASSEMBLER_ -EL "
    ENV["LINK"]      = "#{ENV["LD"]} -A mips32r2  -EL --allow-multiple-definition -T#{File.join(ENV["POSLIBDIR"], "sldscript_d210")} -L#{File.join(MUSL_ROOT, "lib")} -I#{File.join(MUSL_ROOT, "lib")}  -L#{GCC_PAX_LIB} -L#{ENV['POSLIBDIR']} -L#{ENV['LOCOBJ']} "
    ENV["OBJ"]       = BIN.join(" ")

    ::CLEAN.include "out/obj/*.o"
    ::CLOBBER.include "out/obj/*.bin", "out/obj/*.dasm", "out/obj/*.elf"
  end

  ENV["LOCOBJ"]    = File.join(MRUBY_PAX_ROOT, "out", "obj")
  ENV["POSLIBDIR"] = File.join(PAX_LIB_ROOT, "postype", "d210")

  rule '.o' => ["%{out/obj,src}X.c"] do |t|
    sh "#{ENV["GCC"]} #{t.source} -o #{t.name}"
  end

  rule '.o' => ["%{out/obj,test}X.c"] do |t|
    sh "#{ENV["GCC"]} #{t.source} -o #{t.name}"
  end

  rule File.join(ENV['LOCOBJ'], "init.o") => [File.join(ENV['POSLIBDIR'], "init_d210.s")] do |t|
    sh "#{ENV["ASM"]} #{t.source} -o #{t.name}"
  end

  SRC = FileList["src/*.c", "test/*c"]
  BIN = SRC.pathmap("%{test,out/obj}X.o").pathmap("%{src,out/obj}X.o")

  SRC.insert(0, File.join(ENV['POSLIBDIR'], "init_d210.s"))
  BIN.insert(0, File.join(ENV['LOCOBJ'], "init.o"))

  task :link => BIN do
    sh "#{ENV['LINK']} -o #{File.join(ENV['LOCOBJ'], "#{ENV['NAME']}.elf")} #{BIN.join(" ")} #{File.join(MRUBY_LIB, "build", "pax", "lib", "libmruby.a")} #{File.join(ENV["POSLIBDIR"], "libd210api.a")} #{File.join(MUSL_ROOT, "lib", "libc.a")} -ld210api -lc"
    sh "#{File.join(GCC_PAX_BIN, "sde-conv.exe")} -f bin -v -o #{File.join(ENV['LOCOBJ'], "robot_rock-#{PAX.version}.bin")} #{File.join(ENV['LOCOBJ'], "#{ENV['NAME']}.elf")} "
    sh "#{File.join(GCC_PAX_BIN, "sde-objdump.exe")} -D -S #{File.join(ENV['LOCOBJ'], "#{ENV['NAME']}.elf")} > #{File.join(ENV['LOCOBJ'], "#{ENV['NAME']}.dasm")} "
  end

  desc "Clobber/Clean PAX"
  task :clean => [:setup] do
    # Allow task to invoke again
    Rake::Task['clean'].reenable
    Rake::Task['clobber'].reenable

    Rake::Task['clobber'].invoke
  end

  desc "Compile PAX"
  task :compile => [:setup, :link]
end
