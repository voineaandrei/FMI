package proiect.database;

import javax.xml.crypto.Data;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.*;

public class Database {
    private String  URL, user, password;
    public static Connection connection;

    public Database() throws SQLException {
        this.URL = "jdbc:mysql://localhost:3306/appstore";
        this.user = "root";
        this.password = "Parola12341";
        this.connection = DriverManager.getConnection(URL, user, password);
    }

    public Database(String URL, String user, String password){
        this.URL = URL;
        this.user = user;
        this.password = password;
        this.connection = null;
    }

    public void getConnection() {
        try {
            connection = DriverManager.getConnection(URL, user, password);
        } catch (SQLException ex) {
            System.out.println("Error getting connection: " + ex.getMessage());
            System.exit(-1);
        } catch (Exception ex) {
            System.out.println("Error: " + ex.getMessage());
            System.exit(-1);
        }
    }
}