def decode(originalFile, encodedFile, offset)

    File.open(originalFile, "rb") do |file1|
        File.open(encodedFile, "rb") do |file2|

            byte1 = 0
            byte2 = 0

        
            file1.seek(offset + 1, IO::SEEK_SET)
            file2.seek(offset + 1, IO::SEEK_SET)
            
            endCtr = 0
            binaryString = ""

            while endCtr < 8

                byte1 = file1.read(1)
                byte2 = file2.read(1)

                value1 = byte1.unpack1("C")
                value2 = byte2.unpack1("C")
        
                msgBit = value1 ^ value2

                if msgBit == 0
                    endCtr += 1
                else
                    endCtr = 0
                end
                
                binaryString << msgBit.to_s
                

            end

            ascii_string = binaryString.scan(/.{8}/).map { |byte| byte.to_i(2).chr }.join

            puts "Your secret message is: #{ascii_string}" 

        end
    end
end
