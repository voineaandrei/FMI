package proiect.appstore.user;

import proiect.service.AuditService;

public class Card {
    private long cardNumber;
    private float money;
    private ExpirationDate expirationDate;
    private AuditService auditService = AuditService.getAuditService();
    // CONSTRUCTORS

    public Card(){
        this(0, 0);
        this.expirationDate = new ExpirationDate();
        auditService.writeData("Card - add");
    }

    public Card(long cardNumber, float money) {
        this.cardNumber = cardNumber;
        this.money = money;
        this.expirationDate = new ExpirationDate();
        auditService.writeData("Card - add");
    }

    public Card(long cardNumber, float money, ExpirationDate expirationDate) {
        this.cardNumber = cardNumber;
        this.money = money;
        this.expirationDate = expirationDate;
        auditService.writeData("Card - add");
    }

    @Override
    public String toString() {
        if (expirationDate.getMonth() != 0 && expirationDate.getYear() != 0)
            return "Mai aveti " + money + " RON, iar cardul expira pe " + expirationDate.getMonth() + "/" + expirationDate.getYear() + '\n';
        else
            return "Mai aveti " + money + " RON" + '\n';

    }

// SETTERS AND GETTERS

    public ExpirationDate getExpirationDate() {
        return expirationDate;
    }

    public void setExpirationDate(ExpirationDate expirationDate) {
        this.expirationDate = expirationDate;
    }

    public long getCardNumber() {
        return cardNumber;
    }

    public void setCardNumber(long cardNumber) {
        this.cardNumber = cardNumber;
    }

    public float getMoney() {
        return money;
    }

    public void setMoney(float money) {
        this.money = money;
    }
}
