package proiect.service;


import proiect.appstore.user.User;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class UserCSVService {

    public static UserCSVService userCSVService = new UserCSVService();
    private UserService userService = UserService.getUserService();

    public static UserCSVService getUserCSVService() {
        return userCSVService;
    }

    public void readData() {
        Path path = Paths.get("User.csv");
        try (var input = Files.newBufferedReader(path)) {
            String line;
            int noLine = 0;
            while ((line = input.readLine()) != null){
                String[] value = line.split(",");
                userService.add(new User(value[0], value[1], value[2]));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void writeData(){
        Path path = Paths.get("User.csv");
        try (var output = Files.newBufferedWriter(path)) {
            for (User user : userService.getUsers()) {
                output.write(user.getLastName());
                output.write(",");
                output.write(user.getFirstName());
                output.write(",");
                output.write(user.getUsername());
                output.newLine();
                output.flush();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
