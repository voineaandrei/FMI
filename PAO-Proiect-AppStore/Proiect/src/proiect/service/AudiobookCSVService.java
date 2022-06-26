package proiect.service;


import proiect.appstore.applications.Application;
import proiect.appstore.applications.Audiobook;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class AudiobookCSVService {

    public static AudiobookCSVService audiobookCSVService = new AudiobookCSVService();
    ApplicationService applicationService = ApplicationService.getApplicationService();

    public static AudiobookCSVService getAudiobookCSVService() {
        return audiobookCSVService;
    }

    public void readData() {
        Path path = Paths.get("Audiobook.csv");
        try (var input = Files.newBufferedReader(path)) {
            String line;
            int noLine = 0;
            while ((line = input.readLine()) != null){
                String[] value = line.split(",");
                applicationService.add(new Audiobook(value[0], value[1], Float.parseFloat(value[2]), value[3], Integer.parseInt(value[4])));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void writeData(){
        Path path = Paths.get("Audiobook.csv");
        try (var output = Files.newBufferedWriter(path)) {
            for (Audiobook audiobook : applicationService.getAudiobooks()) {
                output.write(audiobook.getPublisherName());
                output.write(",");
                output.write(audiobook.getApplicationName());
                output.write(",");
                output.write(Float.toString(audiobook.getPrice()));
                output.write(",");
                output.write(audiobook.getNarratedBy());
                output.write(",");
                output.write(Integer.toString(audiobook.getDuration()));
                output.newLine();
                output.flush();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
