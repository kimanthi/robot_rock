class Device
  self.adapter = PAX

  def self.version
    "0.4.2"
  end

  # TODO Scalone: temporaly
  class IO
    def self.get_string(min, max)
      PAX._gets(min, max)
    end
  end
end