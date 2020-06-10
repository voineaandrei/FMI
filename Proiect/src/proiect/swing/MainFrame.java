package proiect.swing;

import net.miginfocom.layout.Grid;
import proiect.appstore.applications.Audiobook;
import proiect.appstore.applications.Game;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.SQLException;

public class MainFrame extends JFrame {
    private AudiobookFrame audiobookFrame = new AudiobookFrame("Audiobooks");
    private BookFrame bookFrame = new BookFrame("Books");
    private GameFrame gameFrame = new GameFrame("Games");
    private MovieFrame movieFrame = new MovieFrame("Movies");
    private UsersFrame usersFrame = new UsersFrame("Users");

    public MainFrame(String title) throws SQLException {
        super(title);
        setSize(500, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
        Dimension dimension = Toolkit.getDefaultToolkit().getScreenSize();
        this.setLocation(dimension.width/2 - this.getSize().width/2, dimension.height/2 - this.getSize().height/2);


        // LAYOUT MANAGER
        setLayout(new GridBagLayout());
        GridBagConstraints gc = new GridBagConstraints();
        this.getContentPane().setBackground(Color.orange);


        // BUTOANE
        JButton buttonAudiobooks = new JButton("Audiobooks");
        JButton buttonBooks = new JButton("Books");
        JButton buttonMovies = new JButton("Movies");
        JButton buttonGames = new JButton("Games");
        JButton buttonUsers = new JButton("Users");


        // AMPLASAREA
        gc.weightx = 0.5;
        gc.weighty = 0.5;

        gc.gridx = 0;
        gc.gridy = 0;
        gc.ipady = 30;
        gc.ipadx = 50;
        add(buttonAudiobooks, gc);

        gc.gridx = 2;
        gc.gridy = 0;
        gc.ipady = 30;
        gc.ipadx = 50;
        add(buttonBooks, gc);

        gc.gridx = 0;
        gc.gridy = 2;
        gc.ipady = 30;
        gc.ipadx = 30;
        add(buttonMovies, gc);

        gc.gridx = 2;
        gc.gridy = 2;
        gc.ipady = 30;
        gc.ipadx = 30;
        add(buttonGames, gc);

        gc.fill = GridBagConstraints.HORIZONTAL;
        gc.gridwidth = 3;
        gc.insets = new Insets(0, 20, 0, 20); // external padding
        gc.ipady = 40;
        gc.gridx = 0;
        gc.gridy = 1;
        add(buttonUsers, gc);

        // Add behaviour
        buttonAudiobooks.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                setVisible(false);
                audiobookFrame.setVisible(true);
            }
        });

        buttonBooks.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                setVisible(false);
                bookFrame.setVisible(true);
            }
        });

        buttonMovies.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                setVisible(false);
                movieFrame.setVisible(true);
            }
        });

        buttonGames.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                setVisible(false);
                gameFrame.setVisible(true);
            }
        });

        buttonUsers.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                setVisible(false);
                usersFrame.setVisible(true);
            }
        });
    }
}
