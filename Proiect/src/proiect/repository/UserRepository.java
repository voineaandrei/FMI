package proiect.repository;

import proiect.appstore.user.User;

import java.util.ArrayList;
import java.util.List;

public class UserRepository {
    private List<User> users = new ArrayList<>();

    public void add(User user){
        users.add(user);
    }

    public void add(List<User> users){
        this.users.addAll(users);
    }

    public List<User> getUsers() {
        return users;
    }
}
