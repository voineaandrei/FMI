package proiect.repository;

import proiect.appstore.applications.*;
import proiect.appstore.user.Card;
import proiect.appstore.user.ExpirationDate;
import proiect.appstore.user.User;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DBRepository {
    private static Connection connection;

    public DBRepository(Connection con) {
        this.connection = con;
    }

    public static void addGame(Game game) throws SQLException {
        String sql = "insert into game values (?, ?, ?, ?, ?, ?, ?, ?)";

        PreparedStatement statement = connection.prepareStatement(sql);
        statement.setString(1, game.getPublisherName());
        statement.setString(2, game.getApplicationName());
        statement.setFloat(3, game.getPrice());
        statement.setInt(4, game.getDetails().getNumberOfDownloads());
        statement.setInt(5, game.getDetails().getNumberOfVotes());
        statement.setFloat(6, game.getDetails().getRating());
        statement.setString(7, game.getGenre());
        statement.setBoolean(8, game.isMultiplayer());

        statement.executeUpdate();
        statement.close();
    }

    public static void deleteGame(String appName) throws SQLException {
        String sql = "delete from game where applicationName = ?";
        PreparedStatement statement = connection.prepareStatement(sql);
        statement.setString(1, appName);
        statement.executeUpdate();
    }

    public List<Game> getGames() throws SQLException {
        List<Game> games = new ArrayList<>();

        String sql = "select * from game";
        PreparedStatement statement = connection.prepareStatement(sql);

        ResultSet result = statement.executeQuery();
        while (result.next()) {
            Game g = new Game(result.getString(1), result.getString(2), result.getFloat(3), result.getString(7), result.getBoolean(8));
            g.getDetails().setNumberOfDownloads(result.getInt(4));
            g.getDetails().setNumberOfVotes(result.getInt(5));
            g.getDetails().setRating(result.getFloat(6));

            games.add(g);
        }

        return games;
    }

    public static void addMovie(Movie movie) throws SQLException {
        String sql = "insert into movie values (?, ?, ?, ?, ?, ?, ?, ?, ?)";

        PreparedStatement statement = connection.prepareStatement(sql);
        statement.setString(1, movie.getPublisherName());
        statement.setString(2, movie.getApplicationName());
        statement.setFloat(3, movie.getPrice());
        statement.setInt(4, movie.getDetails().getNumberOfDownloads());
        statement.setInt(5, movie.getDetails().getNumberOfVotes());
        statement.setFloat(6, movie.getDetails().getRating());
        statement.setString(7, movie.getDirectorName());
        statement.setString(8, movie.getSubtitles());
        statement.setBoolean(9, movie.isForKids());

        statement.executeUpdate();
        statement.close();
    }

    public static void deleteMovie(String appName) throws SQLException {
        String sql = "delete from movie where applicationName = ?";
        PreparedStatement statement = connection.prepareStatement(sql);
        statement.setString(1, appName);
        statement.executeUpdate();
    }

    public List<Movie> getMovies() throws SQLException {
        List<Movie> movies = new ArrayList<>();

        String sql = "Select * from movie";
        PreparedStatement statement = connection.prepareStatement(sql);

        ResultSet result = statement.executeQuery();
        while (result.next()) {
            Movie m = new Movie(result.getString(1), result.getString(2), result.getFloat(3), result.getString(7), result.getString(8), result.getBoolean(9));
            m.getDetails().setNumberOfDownloads(result.getInt(4));
            m.getDetails().setNumberOfVotes(result.getInt(5));
            m.getDetails().setRating(result.getFloat(6));

            movies.add(m);
        }

        return movies;
    }

    public static void addBook(Book book) throws SQLException {
        String sql = "insert into book values (?, ?, ?, ?, ?, ?, ?, ?, ?)";

        PreparedStatement statement = connection.prepareStatement(sql);
        statement.setString(1, book.getPublisherName());
        statement.setString(2, book.getApplicationName());
        statement.setFloat(3, book.getPrice());
        statement.setInt(4, book.getDetails().getNumberOfDownloads());
        statement.setInt(5, book.getDetails().getNumberOfVotes());
        statement.setFloat(6, book.getDetails().getRating());
        statement.setInt(7, book.getNumberOfPages());
        statement.setString(8, book.getGenre());
        statement.setString(9, book.getAuthor());

        statement.executeUpdate();
        statement.close();
    }

    public static void deleteBook(String appName) throws SQLException {
        String sql = "delete from book where applicationName = ?";
        PreparedStatement statement = connection.prepareStatement(sql);
        statement.setString(1, appName);
        statement.executeUpdate();
    }

    public List<Book> getBooks() throws SQLException {
        List<Book> books = new ArrayList<>();

        String sql = "Select * from book";
        PreparedStatement statement = connection.prepareStatement(sql);

        ResultSet result = statement.executeQuery();
        while (result.next()) {
            Book b = new Book(result.getString(1), result.getString(2), result.getFloat(3), result.getInt(7), result.getString(8), result.getString(9));
            b.getDetails().setNumberOfDownloads(result.getInt(4));
            b.getDetails().setNumberOfVotes(result.getInt(5));
            b.getDetails().setRating(result.getFloat(6));

            books.add(b);
        }

        return books;
    }

    public static void addAudiobook(Audiobook audiobook) throws SQLException {
        String sql = "insert into audiobook values (?, ?, ?, ?, ?, ?, ?, ?)";

        PreparedStatement statement = connection.prepareStatement(sql);
        statement.setString(1, audiobook.getPublisherName());
        statement.setString(2, audiobook.getApplicationName());
        statement.setFloat(3, audiobook.getPrice());
        statement.setInt(4, audiobook.getDetails().getNumberOfDownloads());
        statement.setInt(5, audiobook.getDetails().getNumberOfVotes());
        statement.setFloat(6, audiobook.getDetails().getRating());
        statement.setString(7, audiobook.getNarratedBy());
        statement.setInt(8, audiobook.getDuration());

        statement.executeUpdate();
        statement.close();
    }

    public static void deleteAudibook(String appName) throws SQLException {
        String sql = "delete from audiobook where applicationName = ?";
        PreparedStatement statement = connection.prepareStatement(sql);
        statement.setString(1, appName);
        statement.executeUpdate();
    }

    public List<Audiobook> getAudiobooks() throws SQLException {
        List<Audiobook> audiobooks = new ArrayList<>();

        String sql = "Select * from audiobook";
        PreparedStatement statement = connection.prepareStatement(sql);

        ResultSet result = statement.executeQuery();
        while (result.next()) {
            Audiobook a = new Audiobook(result.getString(1), result.getString(2), result.getFloat(3), result.getString(7), result.getInt(8));
            a.getDetails().setNumberOfDownloads(result.getInt(4));
            a.getDetails().setNumberOfVotes(result.getInt(5));
            a.getDetails().setRating(result.getFloat(6));

            audiobooks.add(a);
        }

        return audiobooks;
    }

    public static void addUser(User user) throws SQLException {
        String sql;
        PreparedStatement statement;

        if (user.getCard() == null) {
            sql = "insert into users values (?, ?, ?, ?, 0, 0, 0, 0)";
            statement = connection.prepareStatement(sql);
        }
        else {
            sql = "insert into users values (?, ?, ?, ?, ?, ?, ?, ?)";
            statement = connection.prepareStatement(sql);
            statement.setLong(5, user.getCard().getCardNumber());
            statement.setFloat(6, user.getCard().getMoney());
            statement.setInt(7, user.getCard().getExpirationDate().getMonth());
            statement.setInt(8, user.getCard().getExpirationDate().getYear());
        }

        statement.setInt(1, user.getIdCurrent());
        statement.setString(2, user.getUsername());
        statement.setString(3, user.getLastName());
        statement.setString(4, user.getFirstName());
        statement.executeUpdate();
        statement.close();
    }

    public static void deleteUser(int id) throws SQLException {
        String sql = "delete from users where idCurrent = ?";
        PreparedStatement statement = connection.prepareStatement(sql);
        statement.setInt(1, id);
        statement.executeUpdate();
    }

    public List<User> getUsers() throws SQLException {
        List<User> users = new ArrayList<>();

        String sql = "select * from users";
        PreparedStatement statement = connection.prepareStatement(sql);

        ResultSet result = statement.executeQuery();
        while (result.next()) {
            User u = new User(result.getString(3), result.getString(4), result.getString(2));
            ExpirationDate expDate = new ExpirationDate();
            if (result.getInt(7) != 0 && result.getInt(8) != 0) {
                expDate.setMonth(result.getInt(7));
                expDate.setYear(result.getInt(8));
            }
            if (result.getLong(5) != 0) {
                Card c = new Card(result.getLong(5), result.getFloat(6), expDate);
                u.setCard(c);
            }

            users.add(u);
        }

        return users;
    }

    public void addCard(int id, Card card) throws SQLException{
        String sql = "UPDATE users SET cardNumber = ?, money = ?, month = ?, year = ? WHERE idCurrent = ?";
        PreparedStatement statement = connection.prepareStatement(sql);
        statement.setLong(1, card.getCardNumber());
        statement.setFloat(2, card.getMoney());
        statement.setInt(3, card.getExpirationDate().getMonth());
        statement.setInt(4, card.getExpirationDate().getYear());
        statement.setInt(5, id);
        statement.executeUpdate();
        statement.close();
    }

    public void buyApplication(int id, String appName) throws SQLException {
        String sql = "select * from users where idCurrent = ?";
        PreparedStatement statement = connection.prepareStatement(sql);
        statement.setInt(1, id);
        ResultSet result = statement.executeQuery();
        result.next();
        float userMoney = result.getFloat(6);
        String username = result.getString(2);

        List<Game> games = getGames();
        List<Movie> movies = getMovies();
        List<Book> books = getBooks();
        List<Audiobook> audiobooks = getAudiobooks();
        Application application = null;

        for (Game g: games){
            if (g.getApplicationName().equalsIgnoreCase(appName)) {
                application = g;
            }
        }

        for (Movie m: movies){
            if (m.getApplicationName().equalsIgnoreCase(appName)){
                application = m;
            }
        }

        for (Book b: books){
            if (b.getApplicationName().equalsIgnoreCase(appName)){
                application = b;
            }
        }

        for (Audiobook a: audiobooks){
            if (a.getApplicationName().equalsIgnoreCase(appName)){
                application = a;
            }
        }

        if (application != null) {
            if (application.getPrice() <= userMoney) {
                String sqlInsert = "insert into owning values (?, ?)";
                PreparedStatement statement1 = connection.prepareStatement(sqlInsert);
                statement1.setInt(1, id);
                statement1.setString(2, appName);
                statement1.executeUpdate();
                statement1.close();

                String sqlUpdate = "UPDATE users SET money = ? WHERE idCurrent = ?";
                PreparedStatement statement2 = connection.prepareStatement(sqlUpdate);
                statement2.setFloat(1, userMoney - application.getPrice());
                statement2.setInt(2, id);
                statement2.executeUpdate();
                statement2.close();

                int numOfDownloads = application.getDetails().getNumberOfDownloads();
                String sqlUpdate2 = "UPDATE " + application.getType() + " SET numberOfDownloads = ? WHERE applicationName = ?";
                PreparedStatement statement3 = connection.prepareStatement(sqlUpdate2);
                statement3.setInt(1, numOfDownloads + 1);
                statement3.setString(2, appName);
                statement3.executeUpdate();
                statement3.close();
            }
            else
            {
                System.out.println("User-ul " + username + " nu are suficienti bani. " +
                        "Are doar " + userMoney + ", pe cand aplicatia '" +
                        appName + "' costa " + application.getPrice() + "!");
            }
        }
        else {
            System.out.println("Nu exista aplicatia cautata");
        }
    }

    public void createTable(String tableName) throws SQLException{
        String sql = "create table `appstore`.`" + tableName + "`";

        switch (tableName){
            case "game":
                sql += "( `publisherName` VARCHAR(45) NULL, `applicationName` VARCHAR(45) NOT NULL, " +
                        "`price` FLOAT NULL, `numberOfDownloads` INT NULL, " +
                        "`numberOfVotes` INT NULL, `rating` FLOAT NULL, `genre` VARCHAR(45) NULL, " +
                        "`isMultiplayer` TINYINT NULL,  PRIMARY KEY (`applicationName`));";
                break;
            case "movie":
                sql += "( `publisherName` VARCHAR(45) NULL, `applicationName` VARCHAR(45) NOT NULL, " +
                        "`price` FLOAT NULL, `numberOfDownloads` INT NULL, " +
                        "`numberOfVotes` INT NULL, `rating` FLOAT NULL, `directorName` VARCHAR(45) NULL, " +
                        "`subtitles` VARCHAR(45) NULL, `forKids` TINYINT NULL, PRIMARY KEY (`applicationName`));";
                break;
            case "book":
                sql += "( `publisherName` VARCHAR(45) NULL, `applicationName` VARCHAR(45) NOT NULL, " +
                        "`price` FLOAT NULL, `numberOfDownloads` INT NULL, " +
                        "`numberOfVotes` INT NULL, `rating` FLOAT NULL, `numberOfPages` INT NULL, " +
                        "`genre` VARCHAR(45) NULL, `author` VARCHAR(45) NULL,  PRIMARY KEY (`applicationName`));";
                break;
            case "audiobook":
                sql += "( `publisherName` VARCHAR(45) NULL, `applicationName` VARCHAR(45) NOT NULL, " +
                        "`price` FLOAT NULL, `numberOfDownloads` INT NULL, " +
                        "`numberOfVotes` INT NULL, `rating` FLOAT NULL, `narratedBy` VARCHAR(45) NULL, " +
                        "`duration` INT NULL,  PRIMARY KEY (`applicationName`));";
                break;
            case "users":
                sql += "(`idCurrent` INT, `username` VARCHAR(45) NOT NULL, " +
                        "`lastName` VARCHAR(45) NOT NULL, `firstName` VARCHAR(45) NOT NULL, " +
                        "`cardNumber` BIGINT NULL, `money` FLOAT NULL, `month` INT NULL, `year` INT NULL, " +
                        "PRIMARY KEY(`idCurrent`));";
                break;
            case "owning":
                sql += "(`idCurrent` INT NOT NULL, `applicationName` VARCHAR(45) NOT NULL, " +
                        "PRIMARY KEY(`idCurrent`, `applicationName`));";
                break;
            default:
                sql += "( `testTable` INT NOT NULL, PRIMARY KEY (`testTable`));";
                break;
        }
        PreparedStatement statement = connection.prepareStatement(sql);
        statement.executeUpdate();
        statement.close();
    }

    public void deleteTable(String tableName) throws SQLException{
        String sql = "drop table `appstore`.`" + tableName + "`;";
        PreparedStatement statement = connection.prepareStatement(sql);
        statement.executeUpdate();
        statement.close();
    }
}
