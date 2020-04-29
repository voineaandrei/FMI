package proiect.service;


import proiect.appstore.applications.Application;
import proiect.appstore.applications.Movie;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class MovieCSVService {

    public static MovieCSVService movieCSVService = new MovieCSVService();
    ApplicationService applicationService = ApplicationService.getApplicationService();

    public static MovieCSVService getMovieCSVService() {
        return movieCSVService;
    }

    public void readData() {
        Path path = Paths.get("Movie.csv");
        try (var input = Files.newBufferedReader(path)) {
            String line;
            int noLine = 0;
            while ((line = input.readLine()) != null){
                String[] value = line.split(",");
                applicationService.add(new Movie(value[0], value[1], Float.parseFloat(value[2]), value[3], value[4], Boolean.parseBoolean(value[5])));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void writeData(){
        Path path = Paths.get("Movie.csv");
        try (var output = Files.newBufferedWriter(path)) {
            for (Movie movie : applicationService.getMovies()) {
                output.write(movie.getPublisherName());
                output.write(",");
                output.write(movie.getApplicationName());
                output.write(",");
                output.write(Float.toString(movie.getPrice()));
                output.write(",");
                output.write(movie.getDirectorName());
                output.write(",");
                output.write(movie.getSubtitles());
                output.write(",");
                output.write(Boolean.toString(movie.isForKids()));
                output.newLine();
                output.flush();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
