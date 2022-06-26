package proiect.swing;

import proiect.appstore.applications.Game;
import proiect.database.Database;
import proiect.service.DBService;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.sql.SQLException;

public class GameFrame extends JFrame {
    private static Database database;

    static {
        try {
            database = new Database();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static DBService dbService = new DBService(database.connection);

    public GameFrame(String title) throws SQLException {
        super(title);
        setSize(800, 600);

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Dimension dimension = Toolkit.getDefaultToolkit().getScreenSize();
        this.setLocation(dimension.width/2 - this.getSize().width/2, dimension.height/2 - this.getSize().height/2);

        JLabel text = new JLabel("Add game: ");
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

        JLabel genreLabel = new JLabel("Genre: ");
        JTextField genreTextField = new JTextField();
        genreLabel.setBounds(50,250,200,30);
        genreTextField.setBounds(120,250,150,30);
        this.add(genreLabel);
        this.add(genreTextField);

        JLabel isMPLabel = new JLabel("is Multiplayer: ");
        JTextField isMPTextField = new JTextField();
        isMPLabel.setBounds(20,300,200,30);
        isMPTextField.setBounds(120,300,150,30);
        this.add(isMPLabel);
        this.add(isMPTextField);

        JPanel gamePanel = new JPanel();
        JButton jButtonAdd = new JButton("Add!");
        jButtonAdd.addActionListener(addGame(publisherNameTextField, applicationNameTextField, priceTextField, genreTextField, isMPTextField));
        jButtonAdd.setBounds(110,350,100,30);
        gamePanel.add(jButtonAdd);
        gamePanel.setLayout(new BorderLayout());

        JButton backButton = new JButton("Go to Main Page");
        backButton.addActionListener(goToMainPage());
        backButton.setBounds(20, 500, 200, 30);
        gamePanel.add(backButton);
        gamePanel.setLayout(new BorderLayout());

        JList<Game> games = new JList<>();
        games.setBounds(500, 90, 200, 100);
        games.setListData(getGamesArray());
        gamePanel.add(games);
        gamePanel.setLayout(new BorderLayout());

        JButton deleteButton = new JButton("Delete!");
        deleteButton.addActionListener(delete(games));
        deleteButton.setBounds(550, 500, 200, 30);
        gamePanel.add(deleteButton);
        gamePanel.setLayout(new BorderLayout());
        this.add(gamePanel);

    }

    private ActionListener delete(JList<Game> list){
        ActionListener actionListener = actionEvent -> {
            try {
                dbService.deleteGame(list.getSelectedValue().getApplicationName());
            } catch (SQLException e) {
                e.printStackTrace();
            }
        };
        return actionListener;
    }


    private ActionListener addGame(JTextField publisherNameTextField, JTextField applicationNameTextField, JTextField priceTextField, JTextField genreTextField, JTextField isMPTextField) {
        ActionListener actionListener = actionEvent -> {
            String pN = publisherNameTextField.getText();
            String aN = applicationNameTextField.getText();
            String pr = priceTextField.getText();
            float price = Float.parseFloat(pr);
            String genre = genreTextField.getText();
            String isMP = isMPTextField.getText();
            boolean isMultiplayer = Boolean.parseBoolean(isMP);
            Game game = new Game(pN, aN, price, genre, isMultiplayer);
            try {
                dbService.addGame(game);
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

    private static Game[] getGamesArray() throws SQLException{
        return dbService.getGames().toArray(new Game[0]);
    }
}
