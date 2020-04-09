package proiect.Main;
import proiect.appstore.applications.*;
import proiect.appstore.user.Card;
import proiect.appstore.user.ExpirationDate;
import proiect.appstore.user.User;

import java.util.ArrayList;
import java.util.List;

import static proiect.service.ApplicationService.applicationService;
import static proiect.service.UserService.userService;

public class Main {
    public static void main(String[] args) {
        // Useri
        List<User> users = new ArrayList<>();
        users.add(new User("Voinea", "Andrei", "VAndi"));
        users.add(new User("Badea", "Eduard", "Edi"));
        users.add(new User("Cimpian", "Alex", "Cimpi"));

        // Aplicatii
        List<Application> applications = new ArrayList<>();
        applications.add(new Book("Bloomsbury", "Harry Potter", 299, 800, "Fantasy", "J.K.Rowling"));
        applications.add(new Book("Scribner", "All the Light We Cannot See", 239.50f, 630, "Historical Fiction", "Anthony Doerr"));
        applications.add(new Book("Grove Press", "Games People Play", 120.50f, 216, "Psychological", "Eric Berne"));
        applications.add(new Audiobook("M.C.N", "M.C.N. Podcast", 50, "Micutzu", 120));
        applications.add(new Movie("Netflix", "Sherlock Holmes", 120, "Guy Ritchie", "english", true));
        applications.add(new Game("Riot Games", "Valorant", 150, "Shooter", true));

        // Ii adaugam in repository
        userService.add(users);
        userService.add(new User("Florea", "Radu", "Flo12"));
        applicationService.add(applications);
        applicationService.add(new Game("Blizzard", "World of Warcraft", 200, "RPG", true));

        // Adaugam card, cumparam
        userService.addCard("VAndi", new Card(12341, 230.67f, new ExpirationDate(5,2077)));
        userService.buyApplication("VAndi", "Valorant");

        // Afisam userii
        userService.showUsers();

        // Incercam sa arat rating-ul aplicatiei, dar nu a fost votat, asa ca o sa arate mesaj corespunzator
        applicationService.showRating("Valorant");
        userService.giveRating("VAndi", "Valorant", 5);
        applicationService.showRating("Valorant");

        // Incercam sa-i dam rating unei aplicatii, pe care nu o avem si o sa observam ca nu ne lasa
        userService.giveRating("VAndi", "Sherlock Holmes", 5);
        // Incercam sa-i dam rating unei aplicatii care nu exista si ne avertizeaza.
        userService.giveRating("VAndi", "Game of Thrones", 4);
        // Incercam sa dam rating cu un username care nu exista
        userService.giveRating("Usi", "Sherlock Holmes", 4);
    }
}
