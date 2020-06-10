package proiect.swing;

import proiect.appstore.applications.Game;
import proiect.appstore.applications.Movie;
import proiect.appstore.user.Card;
import proiect.appstore.user.ExpirationDate;
import proiect.appstore.user.User;
import proiect.database.Database;
import proiect.service.DBService;

import javax.swing.*;
import javax.swing.border.Border;
import java.awt.*;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.SQLException;
import java.util.Vector;

public class UsersFrame extends JFrame {
    private static Database database;

    static {
        try {
            database = new Database();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static DBService dbService = new DBService(database.connection);

    public UsersFrame(String title) throws SQLException {
        super(title);
        setSize(800, 600);

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Dimension dimension = Toolkit.getDefaultToolkit().getScreenSize();
        this.setLocation(dimension.width/2 - this.getSize().width/2, dimension.height/2 - this.getSize().height/2);

        JLabel text = new JLabel("Add user: ");
        text.setBounds(150, 20, 200, 30);
        this.add(text);

        JLabel usernameLabel = new JLabel("Username: ");
        JTextField usernameTextField = new JTextField();
        usernameLabel.setBounds(25,100,200,30);
        usernameTextField.setBounds(120,100,150,30);
        this.add(usernameLabel);
        this.add(usernameTextField);

        JLabel lastNameLabel = new JLabel("Last name: ");
        JTextField lastNameTextField = new JTextField();
        lastNameLabel.setBounds(25,150,200,30);
        lastNameTextField.setBounds(120,150,150,30);
        this.add(lastNameLabel);
        this.add(lastNameTextField);

        JLabel firstNameLabel = new JLabel("First name: ");
        JTextField firstNameTextField = new JTextField();
        firstNameLabel.setBounds(25,200,200,30);
        firstNameTextField.setBounds(120,200,150,30);
        this.add(firstNameLabel);
        this.add(firstNameTextField);


        JLabel cardNumberLabel = new JLabel("Card number: ");
        JTextField cardNumberTextField = new JTextField();
        cardNumberLabel.setBounds(20,250,200,30);
        cardNumberTextField.setBounds(120,250,150,30);
        this.add(cardNumberLabel);
        this.add(cardNumberTextField);

        JLabel moneyLabel = new JLabel("Money: ");
        JTextField moneyTextField = new JTextField();
        moneyLabel.setBounds(45,300,200,30);
        moneyTextField.setBounds(120,300,150,30);
        this.add(moneyLabel);
        this.add(moneyTextField);

        JLabel monthLabel = new JLabel("Month: ");
        JTextField monthTextField = new JTextField();
        monthLabel.setBounds(45,350,200,30);
        monthTextField.setBounds(120,350,150,30);
        this.add(monthLabel);
        this.add(monthTextField);

        JLabel yearLabel = new JLabel("Year: ");
        JTextField yearTextField = new JTextField();
        yearLabel.setBounds(45,400,200,30);
        yearTextField.setBounds(120,400,150,30);
        this.add(yearLabel);
        this.add(yearTextField);

        JPanel gamePanel = new JPanel();
        JButton jButtonAdd = new JButton("Add!");
        jButtonAdd.addActionListener(addGame(usernameTextField, lastNameTextField, firstNameTextField, cardNumberTextField, moneyTextField, monthTextField, yearTextField));
        jButtonAdd.setBounds(110,450,100,30);
        gamePanel.add(jButtonAdd);
        gamePanel.setLayout(new BorderLayout());

        JButton backButton = new JButton("Go to Main Page");
        backButton.addActionListener(goToMainPage());
        backButton.setBounds(20, 500, 200, 30);
        gamePanel.add(backButton);
        gamePanel.setLayout(new BorderLayout());

        JList<User> users = new JList<>();
        users.setBounds(500, 90, 200, 100);
        users.setListData(getUsersArray());
        gamePanel.add(users);
        gamePanel.setLayout(new BorderLayout());
        this.add(gamePanel);

        JButton deleteButton = new JButton("Delete!");
        deleteButton.addActionListener(delete(users));
        deleteButton.setBounds(550, 500, 200, 30);
        gamePanel.add(deleteButton);
        gamePanel.setLayout(new BorderLayout());
        this.add(gamePanel);

    }

    private ActionListener delete(JList<User> list){
        ActionListener actionListener = actionEvent -> {
            try {
                dbService.deleteUser(list.getSelectedValue().getIdCurrent());
            } catch (SQLException e) {
                e.printStackTrace();
            }
        };
        return actionListener;
    }

    private ActionListener addGame(JTextField usernameTextField, JTextField lastNameTextField, JTextField firstNameTextField, JTextField cardNumberTextField, JTextField moneyTextField, JTextField monthTextField, JTextField yearFieldText) {
        ActionListener actionListener = actionEvent -> {
            String username = usernameTextField.getText();
            String lastName = lastNameTextField.getText();
            String firstName = firstNameTextField.getText();
            String cardNumberString = cardNumberTextField.getText();
            Long cardNumber = Long.parseLong(cardNumberString);
            String moneyString = moneyTextField.getText();
            Float money = Float.parseFloat(moneyString);
            String monthString = monthTextField.getText();
            Integer month = Integer.parseInt(monthString);
            String yearString = yearFieldText.getText();
            Integer year = Integer.parseInt(yearString);
            ExpirationDate expirationDate = new ExpirationDate(month, year);
            Card card = new Card(cardNumber, money, expirationDate);
            User user = new User(username, lastName, firstName);
            user.setCard(card);
            try {
                dbService.addUser(user);
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

    private static User[] getUsersArray() throws SQLException{
        return dbService.getUsers().toArray(new User[0]);
    }
}