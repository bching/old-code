import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main
{
	public static void main(String[] args) throws IOException
	{
		
		Pattern p = Pattern.compile("([a-zA-Z]*'?[a-zA-Z]+)(?=[ /t]+[a-z]*)");
		
		File inFile = new File("5000wordlist.txt");
		FileReader inFileReader = new FileReader(inFile);
		BufferedReader inBuffFileReader = new BufferedReader(inFileReader);

		File outFile = new File("edited5000wordlist.txt");
		FileWriter outFileWriter = new FileWriter(outFile);
		
		String line;
		int i = 0;
		outFileWriter.write("");
		
		while((line = inBuffFileReader.readLine()) != null)
		{
			Matcher m = p.matcher(line);
			if(m.find())
			{
				String s = m.group(0);
				System.out.println(s);
				outFileWriter.append(m.group(0));
				outFileWriter.append("\n");
			}
		}
		outFileWriter.close();
		inBuffFileReader.close();
	}
}
