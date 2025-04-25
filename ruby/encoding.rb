def encode(inputPath, outputPath, message, offset)

    binaryString = message.bytes.map { |b| b.to_s(2).rjust(8, '0') }.join

    File.open(inputPath, "rb") do |infile|
        File.open(outputPath, "wb") do |outfile|
            byte = 0
                
            for i in 0..offset do
                byte = infile.read(1)
                value = byte.unpack1("C")
                outfile.write([value].pack("C"))
            end
        
            binaryString.each_char do |char|
                byte = infile.read(1)
                msgBit = char.to_i

                value = byte.unpack1("C")
                modifiedByte = value ^ msgBit
                outfile.write([modifiedByte].pack("C"))
            end

            while byte = infile.read(1)
                value = byte.unpack1("C")
                outfile.write([value].pack("C"))
            end
        end
    end

    puts "Your file has been encoded"

end



