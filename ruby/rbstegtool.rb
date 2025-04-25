require_relative 'encoding'
require_relative 'decoding'

offset = 98

print "Choose an option: Encode (1) or Decode(2): "
input = gets.chomp.to_i

case input
when 1
    print "What is the original file?: "
    inputPath = gets.chomp
    outputPath = "encoded.png"
    print "What is the message?: "
    message = gets.chomp
    
    encode(inputPath, outputPath, message, offset)

when 2
    print "What is the original file?: "
    originalFile = gets.chomp
    print "What is the encoded file?: "
    encodedFile = gets.chomp

    decode(originalFile, encodedFile, offset)

else
    puts "Invalid option selected"
end
