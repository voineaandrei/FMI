package proiect.Main;
import proiect.appstore.applications.*;
import proiect.appstore.user.Card;
import proiect.appstore.user.ExpirationDate;
import proiect.appstore.user.User;
import proiect.service.*;

import java.awt.*;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import proiect.database.Database;
import proiect.swing.MainFrame;

import javax.swing.*;

public class Main {
//    private static ApplicationService applicationService = ApplicationService.getApplicationService();
////    private static UserService userService = UserService.getUserService();
////    private static AudiobookCSVService audiobookCSVService = AudiobookCSVService.getAudiobookCSVService();
////    private static BookCSVService bookCSVService = BookCSVService.getBookCSVService();
////    private static MovieCSVService movieCSVService = MovieCSVService.getMovieCSVService();
////    private static GameCSVService gameCSVService = GameCSVService.getGameCSVService();
////    private static UserCSVService userCSVService = UserCSVService.getUserCSVService();
////
////    void Etapa1(){
////        // Useri
////        List<User> users = new ArrayList<>();
////        users.add(new User("Voinea", "Andrei", "VAndi"));
////        users.add(new User("Badea", "Eduard", "Edi"));
////        users.add(new User("Cimpian", "Alex", "Cimpi"));
////
////        // Aplicatii
////        List<Application> applications = new ArrayList<>();
////        applications.add(new Book("Bloomsbury", "Harry Potter", 299, 800, "Fantasy", "J.K.Rowling"));
////        applications.add(new Book("Scribner", "All the Light We Cannot See", 239.50f, 630, "Historical Fiction", "Anthony Doerr"));
////        applications.add(new Book("Grove Press", "Games People Play", 120.50f, 216, "Psychological", "Eric Berne"));
////        applications.add(new Audiobook("M.C.N", "M.C.N. Podcast", 50, "Micutzu", 120));
////        applications.add(new Movie("Netflix", "Sherlock Holmes", 120, "Guy Ritchie", "english", true));
////        applications.add(new Game("Riot Games", "Valorant", 150, "Shooter", true));
////
////        // Ii adaugam in repository
////        userService.add(users);
////        userService.add(new User("Florea", "Radu", "Flo12"));
////        applicationService.add(applications);
////        applicationService.add(new Game("Blizzard", "World of Warcraft", 200, "RPG", true));
////
////        // Adaugam card, cumparam
////        userService.addCard("VAndi", new Card(12341, 230.67f, new ExpirationDate(5,2077)));
////        userService.buyApplication("VAndi", "Valorant");
////
////        // Afisam userii
////        userService.showUsers();
////
////        // Incercam sa aratam rating-ul aplicatiei, dar nu a fost votat, asa ca o sa arate mesaj corespunzator
////        applicationService.showRating("Valorant");
////        userService.giveRating("VAndi", "Valorant", 5);
////        applicationService.showRating("Valorant");
////
////        // Incercam sa-i dam rating unei aplicatii, pe care nu o avem si o sa observam ca nu ne lasa
////        userService.giveRating("VAndi", "Sherlock Holmes", 5);
////        // Incercam sa-i dam rating unei aplicatii care nu exista si ne avertizeaza.
////        userService.giveRating("VAndi", "Game of Thrones", 4);
////        // Incercam sa dam rating cu un username care nu exista
////        userService.giveRating("Usi", "Sherlock Holmes", 4);
////    }
////
////
////    public static void Etapa2() {
////        userCSVService.readData();
////        audiobookCSVService.readData();
////        bookCSVService.readData();
////        gameCSVService.readData();
////        movieCSVService.readData();
////    }

    public static void Etapa3() throws SQLException {
        Database database = new Database("jdbc:mysql://localhost:3306/appstore", "root", "Parola12341");
        database.getConnection();
        DBService DBService = new DBService(database.connection);

        DBService.createTable("randomTable");
        DBService.deleteTable("randomTable");

        DBService.deleteTable("game");
        DBService.deleteTable("movie");
        DBService.deleteTable("book");
        DBService.deleteTable("audiobook");
        DBService.deleteTable("users");
        DBService.deleteTable("owning");

        DBService.createTable("game");
        DBService.createTable("movie");
        DBService.createTable("book");
        DBService.createTable("audiobook");
        DBService.createTable("users");
        DBService.createTable("owning");

        DBService.addGame(new Game("Blizzard", "World of Warcraft", 200, "RPG", true));
        DBService.addGame(new Game("Riot Games", "Valorant", 100, "Shooter", true));
        DBService.addBook(new Book("Bloomsbury", "Harry Potter", 299, 800, "Fantasy", "J.K.Rowling"));
        DBService.addBook(new Book("Scribner", "All the Light We Cannot See", 239.50f, 630, "Historical Fiction", "Anthony Doerr"));
        DBService.addBook(new Book("Grove Press", "Games People Play", 120.50f, 216, "Psychological", "Eric Berne"));
        DBService.addAudiobook(new Audiobook("M.C.N", "M.C.N. Podcast", 50, "Micutzu", 120));
        DBService.addMovie(new Movie("Netflix", "Sherlock Holmes", 120, "Guy Ritchie", "english", true));

        DBService.addUser(new User("Voinea", "Andrei", "VAndi"));
        DBService.addUser(new User("Badea", "Eduard", "Edi"));
        DBService.addUser(new User("Cimpian", "Alex", "Cimpi"));
//        DBService.deleteGame("World of Warcraft");

        DBService.addCard(0, new Card(11223344, 230.67f, new ExpirationDate(5,2077)));
        DBService.addCard(1, new Card(44332211, 104.50f, new ExpirationDate(6, 2065)));
        DBService.addCard(2, new Card(11442233, 500, new ExpirationDate(2, 2080)));

        DBService.buyApplication(0, "Valorant");

        for (Book book: DBService.getBooks()) {
            System.out.println(book.getApplicationName());
        }

    }

    public static void main(String[] args) throws SQLException {
//        Etapa2();
//        userService.addCard("VAndi", new Card(12341, 230.67f, new ExpirationDate(5,2077)));
//        userService.buyApplication("VAndi", "Valorant");
//        applicationService.showApplications();
//        System.out.println();
//        userService.showUsers();
//        userService.giveRating("VAndi", "Valorant", 5);

//        Etapa3();

        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                try {
                    JFrame frame = new MainFrame("Appstore2.0");
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
        });

    }
}
