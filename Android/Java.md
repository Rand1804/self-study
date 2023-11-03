![image-20231102031526560](assets/image-20231102031526560.png)

![image-20231102031534965](assets/image-20231102031534965.png)

![image-20231102031546307](assets/image-20231102031546307.png)

![image-20231102031552051](assets/image-20231102031552051.png)

![image-20231102031600260](assets/image-20231102031600260.png)

![image-20231102031607985](assets/image-20231102031607985.png)![image-20231102032113755](assets/image-20231102032113755.png)

![image-20231102032303941](assets/image-20231102032303941.png)

![image-20231102032846159](assets/image-20231102032846159.png)

抽象方法：在父类中声明，在子类中必须实现的方法

![image-20231102033605373](assets/image-20231102033605373.png)

```java
public interface UserDao {
    int age = 33;
    void myPrint();
}

public class UserTest implements UserDao {
    public void myPrint() {
        System.out.println("test");
    }
}
```

