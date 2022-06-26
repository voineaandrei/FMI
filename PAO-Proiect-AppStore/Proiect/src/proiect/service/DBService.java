package proiect.service;

import proiect.appstore.applications.Audiobook;
import proiect.appstore.applications.Book;
import proiect.appstore.applications.Game;
import proiect.appstore.applications.Movie;
import proiect.appstore.user.Card;
import proiect.appstore.user.User;
import proiect.repository.DBRepository;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.List;

public class DBService {

    private DBRepository DBRepository;
    private AuditService auditService = AuditService.getAuditService();

    public DBService(Connection con){
        DBRepository = new DBRepository(con);
    }

    public void addGame(Game game) throws SQLException{
        DBRepository.addGame(game);
        auditService.writeData("addGame", Thread.currentThread().getName());
    }

    public void deleteGame(String appName) throws SQLException{
        DBRepository.deleteGame(appName);
        auditService.writeData("deleteGame", Thread.currentThread().getName());
    }

    public List<Game> getGames() throws SQLException{
        auditService.writeData("getGames", Thread.currentThread().getName());
        return DBRepository.getGames();
    }

    public void addMovie(Movie movie) throws SQLException{
        DBRepository.addMovie(movie);
        auditService.writeData("addMovie", Thread.currentThread().getName());
    }

    public void deleteMovie(String appName) throws SQLException{
        DBRepository.deleteMovie(appName);
        auditService.writeData("deleteMovie", Thread.currentThread().getName());
    }

    public List<Movie> getMovies() throws SQLException{
        auditService.writeData("getMovies", Thread.currentThread().getName());
        return DBRepository.getMovies();
    }

    public void addBook(Book book) throws SQLException{
        DBRepository.addBook(book);
        auditService.writeData("addBook", Thread.currentThread().getName());
    }

    public void deleteBook(String appName) throws SQLException{
        DBRepository.deleteBook(appName);
        auditService.writeData("deleteBook", Thread.currentThread().getName());
    }

    public List<Book> getBooks() throws SQLException{
        auditService.writeData("getBooks", Thread.currentThread().getName());
        return DBRepository.getBooks();
    }

    public void addAudiobook(Audiobook audiobook) throws SQLException{
        DBRepository.addAudiobook(audiobook);
        auditService.writeData("addAudibook", Thread.currentThread().getName());
    }

    public void deleteAudiobook(String appName) throws SQLException{
        DBRepository.deleteAudibook(appName);
        auditService.writeData("deleteAudiobook", Thread.currentThread().getName());
    }

    public List<Audiobook> getAudiobooks() throws SQLException{
        auditService.writeData("getAudibooks", Thread.currentThread().getName());
        return DBRepository.getAudiobooks();
    }

    public void addUser(User user) throws SQLException{
        DBRepository.addUser(user);
        auditService.writeData("addUser", Thread.currentThread().getName());
    }

    public void deleteUser(int id) throws SQLException{
        DBRepository.deleteUser(id);
        auditService.writeData("deleteUser", Thread.currentThread().getName());
    }

    public List<User> getUsers() throws SQLException{
        auditService.writeData("getUsers", Thread.currentThread().getName());
        return DBRepository.getUsers();
    }

    public void addCard(int id, Card card) throws SQLException{
        DBRepository.addCard(id, card);
        auditService.writeData("addCard", Thread.currentThread().getName());
    }

    public void buyApplication(int id, String appName) throws SQLException{
        DBRepository.buyApplication(id, appName);
        auditService.writeData("buyApplication", Thread.currentThread().getName());
    }

    public void createTable(String tableName) throws SQLException{
        DBRepository.createTable(tableName);
        auditService.writeData("createTable", Thread.currentThread().getName());
    }

    public void deleteTable(String tableName) throws SQLException{
        DBRepository.deleteTable(tableName);
        auditService.writeData("deleteTable", Thread.currentThread().getName());
    }
}
