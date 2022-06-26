package proiect.appstore.user;

public class ExpirationDate {
    private int month, year;

    public ExpirationDate(){
        this(0, 0);
    }
    public ExpirationDate(int month, int year) {
        if (month >= 1 && month <= 12)
            this.month = month;
        else this.month = 0;
        if (year >= 2020)
            this.year = year;
        else this.year = 0;
    }

    public int getMonth() {
        return month;
    }

    public void setMonth(int month) {
        this.month = month;
    }

    public int getYear() {
        return year;
    }

    public void setYear(int year) {
        this.year = year;
    }
}
