package proiect.service;


import proiect.appstore.applications.Application;
import proiect.appstore.applications.Game;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class GameCSVService {

    public static GameCSVService gameCSVService = new GameCSVService();
    ApplicationService applicationService = ApplicationService.getApplicationService();

    public static GameCSVService getGameCSVService() {
        return gameCSVService;
    }

    public void readData() {
        Path path = Paths.get("Game.csv");
        try (var input = Files.newBufferedReader(path)) {
            String line;
            int noLine = 0;
            while ((line = input.readLine()) != null){
                String[] value = line.split(",");
                applicationService.add(new Game(value[0], value[1], Float.parseFloat(value[2]), value[3], Boolean.parseBoolean(value[4])));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void writeData(){
        Path path = Paths.get("Game.csv");
        try (var output = Files.newBufferedWriter(path)) {
            for (Game game : applicationService.getGames()) {
                output.write(game.getPublisherName());
                output.write(",");
                output.write(game.getApplicationName());
                output.write(",");
                output.write(Float.toString(game.getPrice()));
                output.write(",");
                output.write(game.getGenre());
                output.write(",");
                output.write(Boolean.toString(game.isMultiplayer()));
                output.newLine();
                output.flush();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
