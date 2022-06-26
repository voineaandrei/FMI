package proiect.swing;

import proiect.appstore.applications.Audiobook;
import proiect.appstore.applications.Game;
import proiect.database.Database;
import proiect.service.DBService;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.sql.SQLException;

public class AudiobookFrame extends JFrame {
    private static Database database;
    static {
        try {
            database = new Database();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static DBService dbService = new DBService(database.connection);

    public AudiobookFrame(String title) throws SQLException {
        super(title);
        setSize(800, 600);

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Dimension dimension = Toolkit.getDefaultToolkit().getScreenSize();
        this.setLocation(dimension.width/2 - this.getSize().width/2, dimension.height/2 - this.getSize().height/2);

        JLabel text = new JLabel("Add audiobook: ");
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

        JLabel narratedByLabel = new JLabel("Narrated by: ");
        JTextField narratedByTextField = new JTextField();
        narratedByLabel.setBounds(25,250,200,30);
        narratedByTextField.setBounds(120,250,150,30);
        this.add(narratedByLabel);
        this.add(narratedByTextField);

        JLabel durationLabel = new JLabel("Duration: ");
        JTextField durationTextField = new JTextField();
        durationLabel.setBounds(45,300,200,30);
        durationTextField.setBounds(120,300,150,30);
        this.add(durationLabel);
        this.add(durationTextField);

        JPanel gamePanel = new JPanel();
        JButton jButtonAdd = new JButton("Add!");
        jButtonAdd.addActionListener(addAudiobook(publisherNameTextField, applicationNameTextField, priceTextField, narratedByTextField, durationTextField));
        jButtonAdd.setBounds(110,350,100,30);
        gamePanel.add(jButtonAdd);
        gamePanel.setLayout(new BorderLayout());

        JButton backButton = new JButton("Go to Main Page");
        backButton.addActionListener(goToMainPage());
        backButton.setBounds(20, 500, 200, 30);
        gamePanel.add(backButton);
        gamePanel.setLayout(new BorderLayout());

        JList<Audiobook> audiobooks = new JList<>();
        audiobooks.setBounds(500, 90, 200, 100);
        audiobooks.setListData(getAudiobooksArray());
        gamePanel.add(audiobooks);
        gamePanel.setLayout(new BorderLayout());


        JButton deleteButton = new JButton("Delete!");
        deleteButton.addActionListener(delete(audiobooks));
        deleteButton.setBounds(550, 500, 200, 30);
        gamePanel.add(deleteButton);
        gamePanel.setLayout(new BorderLayout());
        this.add(gamePanel);
    }


    private ActionListener delete(JList<Audiobook> list){
        ActionListener actionListener = actionEvent -> {
            try {
                dbService.deleteAudiobook(list.getSelectedValue().getApplicationName());
            } catch (SQLException e) {
                e.printStackTrace();
            }
        };
        return actionListener;
    }

    private ActionListener addAudiobook(JTextField publisherNameTextField, JTextField applicationNameTextField, JTextField priceTextField, JTextField narratedByTextField, JTextField durationTextField) {
        ActionListener actionListener = actionEvent -> {
            String publisherName = publisherNameTextField.getText();
            String applicationName = applicationNameTextField.getText();
            String priceString = priceTextField.getText();
            float price = Float.parseFloat(priceString);
            String narratedBy = narratedByTextField.getText();
            String durationString = durationTextField.getText();
            Integer duration = Integer.parseInt(durationString);
            Audiobook audiobook = new Audiobook(publisherName, applicationName, price, narratedBy, duration);
            try {
                dbService.addAudiobook(audiobook);
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

    private static Audiobook[] getAudiobooksArray() throws SQLException{
        return dbService.getAudiobooks().toArray(new Audiobook[0]);
    }
}
