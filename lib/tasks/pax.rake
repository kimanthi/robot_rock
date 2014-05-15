
MRUBY_PAX_ROOT ||= File.join(File.dirname(File.expand_path(__FILE__)), "..", "..")
MUSL_ROOT      = File.join(MRUBY_PAX_ROOT, "lib", "musl")
PAX_LIB_ROOT   = File.join(MRUBY_PAX_ROOT, "lib", "sdk")
GCC_PAX_PATH   = File.join(PAX_LIB_ROOT, "build", "gcc-sde", "bin")
GCC_PAX_BIN    = File.join(GCC_PAX_PATH, "bin")
LOCINCLUDE     = [File.join(MRUBY_PAX_ROOT, "include"), File.join(MUSL_ROOT, "include"), File.join(PAX_LIB_ROOT, "include")]

ENV["NAME"]    = "mruby-pax"
ENV["PATH"]    = "#{ENV["PATH"]}:/cygdrive/c/WINDOWS:/cygdrive/c/WINDOWS/system32:#{GCC_PAX_BIN}"
ENV["GCCDIR"]  = GCC_PAX_PATH
ENV["GCCBIN"]  = GCC_PAX_BIN
ENV["LOCOBJ"]  = File.join(MRUBY_PAX_ROOT, "obj")
ENV["LOCINC"]  = "-I\"#{LOCINCLUDE.join("\" -I")}\""
ENV["CFLAGS"]  = "-mtune=4ksd -mips32r2 -c -EL -O1 -ffixed-14 -ffixed-15 -G0 -fomit-frame-pointer -Wimplicit -Wformat -ffreestanding -mlong-calls -gdwarf-2 -msoft-float"
ENV["GCC"]     = "#{File.join(GCC_PAX_BIN, "sde-gcc.exe")} #{ENV['CFLAGS']} #{ENV["LOCINC"]}"
ENV["CC"]      = File.join(GCC_PAX_BIN, "sde-gcc.exe")
ENV["AR"]      = File.join(GCC_PAX_BIN, "sde-ar.exe")
ENV['LD']      = File.join(GCC_PAX_BIN, "sde-ld.exe")
ENV['CROSS_COMPILE'] = File.join(GCC_PAX_BIN, "sde-")

MRuby::Toolchain.new(:pax) do |conf|
  [conf.cc, conf.cxx, conf.objc, conf.asm].each do |cc|
    cc.command = ENV["CC"]
    cc.flags = [ENV["CFLAGS"]]
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

  conf.bins = %w(mrbc)
  # include the min GEMs
  conf.gembox 'min'
end

MRuby::CrossBuild.new('pax') do |conf|
  toolchain :pax

  #conf.cc.defines = %w(PAX DISABLE_STDIO EXIT_FAILURE _PTRDIFF_T_ YYFPRINTF YYSTYPE_IS_DECLARED)
  #conf.cc.defines = %w(PAX DISABLE_STDIO EXIT_FAILURE)
  conf.cc.defines = %w(PAX EXIT_FAILURE)
  conf.bins = []
  conf.gembox 'min'
end