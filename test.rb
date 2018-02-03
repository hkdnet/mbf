require 'pathname'

require_relative 'bf.rb'

Dir['./input/**'].each do |f|
  input_path = f
  output_path = "./output/#{f[8..-1]}"
  sio = StringIO.new
  bf = Bf.new(File.read(input_path), out: sio)
  bf.process
  sio.rewind
  actual = sio.read
  expected = File.read(output_path)
  if actual != expected
    STDERR.puts "actual:"
    STDERR.puts  actual
    STDERR.puts "expected:"
    STDERR.puts expected
    raise 'mismatch'
  end
end
