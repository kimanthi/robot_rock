class FileDb < Hash

  attr_accessor :path

  def initialize
    super
  end

  def self.open(path)
    f = self.new
    f.open(path)
    f
  end

  def open(path)
    @path = path
    if File.exist?(path)
      file = File.open(path, "r")
      self.parse(file.read)
    end
  ensure
    file.close if file
  end

  def parse(text)
    text.each_line do |line|
      line = line[0..-2] if line[-1] == "\n" # This seems to be necessary
      key_value = line.split("=")
      self[key_value[0]] = key_value[1]
    end
  end

  def save
    file_new = File.open(@path, "w+")
    self.each do |line_key, line_value|
      file_new.puts("#{line_key}=#{line_value}")
    end
    file_new.close
  end
end