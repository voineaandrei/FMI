package proiect.swing;

import proiect.appstore.applications.Book;
import proiect.appstore.applications.Game;
import proiect.appstore.applications.Movie;
import proiect.database.Database;
import proiect.service.DBService;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.sql.SQLException;

public class MovieFrame extends JFrame {
    private static Database database;

    static {
        try {
            database = new Database();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static DBService dbService = new DBService(database.connection);

    public MovieFrame(String title) throws SQLException {
        super(title);
        setSize(800, 600);

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Dimension dimension = Toolkit.getDefaultToolkit().getScreenSize();
        this.setLocation(dimension.width/2 - this.getSize().width/2, dimension.height/2 - this.getSize().height/2);

        JLabel text = new JLabel("Add movie: ");
        text.setBounds(150, 20, 200, 30);
        this.add(text);

        JLabel publisherNameLabel = new JLabel("Publisher name: ");
        JTextField publisherNameTextField = new JTextField();
        publisherNameLabel.setBounds(20,100,200,30);
        publisherNameTextField.setBounds(120,100,150,30);
        this.add(publisherNameLabel);
        this.add(publisherNameTextField);

        JLabel applicationNameLabel = new JLabel("Application name: ");
        JTextField applicationNameTextField = new JTextField();
        applicationNameLabel.setBounds(15,150,200,30);
        applicationNameTextField.setBounds(120,150,150,30);
        this.add(applicationNameLabel);
        this.add(applicationNameTextField);

        JLabel priceLabel = new JLabel("Price: ");
        JTextField priceTextField = new JTextField();
        priceLabel.setBounds(50,200,200,30);
        priceTextField.setBounds(120,200,150,30);
        this.add(priceLabel);
        this.add(priceTextField);


        JLabel directorNameLabel = new JLabel("Director name: ");
        JTextField directorNameTextField = new JTextField();
        directorNameLabel.setBounds(25,250,200,30);
        directorNameTextField.setBounds(120,250,150,30);
        this.add(directorNameLabel);
        this.add(directorNameTextField);

        JLabel subtitlesLabel = new JLabel("Subtitles: ");
        JTextField subtitlesTextField = new JTextField();
        subtitlesLabel.setBounds(30,300,200,30);
        subtitlesTextField.setBounds(120,300,150,30);
        this.add(subtitlesLabel);
        this.add(subtitlesTextField);

        JLabel forKidsLabel = new JLabel("forKids: ");
        JTextField forKidsTextField = new JTextField();
        forKidsLabel.setBounds(35,350,200,30);
        forKidsTextField.setBounds(120,350,150,30);
        this.add(forKidsLabel);
        this.add(forKidsTextField);

        JPanel gamePanel = new JPanel();
        JButton jButtonAdd = new JButton("Add!");
        jButtonAdd.addActionListener(addMovie(publisherNameTextField, applicationNameTextField, priceTextField, directorNameTextField, subtitlesTextField, forKidsTextField));
        jButtonAdd.setBounds(110,400,100,30);
        gamePanel.add(jButtonAdd);
        gamePanel.setLayout(new BorderLayout());

        JButton backButton = new JButton("Go to Main Page");
        backButton.addActionListener(goToMainPage());
        backButton.setBounds(20, 500, 200, 30);
        gamePanel.add(backButton);
        gamePanel.setLayout(new BorderLayout());

        JList<Movie> movies = new JList<>();
        movies.setBounds(500, 90, 200, 100);
        movies.setListData(getMoviesArray());
        gamePanel.add(movies);
        gamePanel.setLayout(new BorderLayout());
        this.add(gamePanel);

        JButton deleteButton = new JButton("Delete!");
        deleteButton.addActionListener(delete(movies));
        deleteButton.setBounds(550, 500, 200, 30);
        gamePanel.add(deleteButton);
        gamePanel.setLayout(new BorderLayout());
        this.add(gamePanel);

    }


    private ActionListener delete(JList<Movie> list){
        ActionListener actionListener = actionEvent -> {
            try {
                dbService.deleteMovie(list.getSelectedValue().getApplicationName());
            } catch (SQLException e) {
                e.printStackTrace();
            }
        };
        return actionListener;
    }

    private ActionListener addMovie(JTextField publisherNameTextField, JTextField applicationNameTextField, JTextField priceTextField, JTextField directorNameTextField, JTextField subtitlesTextField, JTextField forKidsTextField) {
        ActionListener actionListener = actionEvent -> {
            String pN = publisherNameTextField.getText();
            String aN = applicationNameTextField.getText();
            String pr = priceTextField.getText();
            float price = Float.parseFloat(pr);
            String directorName = directorNameTextField.getText();
            String subtitles = subtitlesTextField.getText();
            String forKidsString = forKidsTextField.getText();
            Boolean forKids = Boolean.parseBoolean(forKidsString);
            Movie movie = new Movie(pN, aN, price, directorName, subtitles, forKids);
            try {
                dbService.addMovie(movie);
            } catch (SQLException e) {
                e.printStackTrace();
            }
        };
        return actionListener;
    }

    private ActionListener goToMainPage(){
        ActionListener actionListener = actionEvent -> {
            try {
                JFrame main = new MainFrame("Appstore 2.0");
                this.setVisible(false);
            } catch (SQLException e) {
                e.printStackTrace();
            }
        };
        return actionListener;
    }

    private static Movie[] getMoviesArray() throws SQLException{
        return dbService.getMovies().toArray(new Movie[0]);
    }
}
