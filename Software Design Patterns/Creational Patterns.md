**Creational Design Patterns**

**Introduction**
Creational design patterns provide various object creation mechanisms, increasing flexibility and reuse of existing code. They abstract the instantiation process, making the system independent of how its objects are created, composed, and represented.

---

## 1. Singleton Pattern

**Intent:** Ensure a class has only one instance and provide a global point of access to it.

**Motivation:** Some resources (e.g., configuration settings, logging) should have exactly one instance to coordinate actions across the system.

**Structure (UML):**

```
+-------------------+
|   Singleton       |
+-------------------+
| -instance: Self   |
+-------------------+
| +getInstance():Self |
+-------------------+
```

**Implementation (Java):**

```java
public class Singleton {
    private static Singleton instance;
    private Singleton() { }
    public static synchronized Singleton getInstance() {
        if (instance == null) {
            instance = new Singleton();
        }
        return instance;
    }
}
```

**Pros:**

- Controlled access to sole instance.
- Reduced namespace pollution.
- Permits refinement of operations and representation.

**Cons:**

- Difficult to unit-test due to global state.
- Can mask bad design (e.g., using global variables).

**Use Cases:** Logging, configuration, thread pool, caching.

---

## 2. Factory Method Pattern

**Intent:** Define an interface for creating an object, but let subclasses decide which class to instantiate.

**Motivation:** Allow a class to defer instantiation to subclasses, promoting loose coupling.

**Structure (UML):**

```
+----------------+      +------------------+
| Creator        |<>----| Product          |
+----------------+      +------------------+
| +factoryMethod()|      |                  |
| +operation()   |      |                  |
+----------------+      +------------------+
         ^                       ^
         |                       |
+----------------+      +------------------+
| ConcreteCreator|      | ConcreteProduct  |
+----------------+      +------------------+
| +factoryMethod()|      |                  |
+----------------+      +------------------+
```

**Implementation (Java):**

```java
public abstract class Dialog {
    public void renderWindow() {
        Button okButton = createButton();
        okButton.render();
    }
    public abstract Button createButton();
}

public class WindowsDialog extends Dialog {
    public Button createButton() {
        return new WindowsButton();
    }
}
```

**Pros:**

- Promotes loose coupling by eliminating the need to bind application-specific classes into code.
- Supports single responsibility principle.

**Cons:**

- Requires additional subclasses for each product type.
- Can increase complexity in the codebase.

**Use Cases:** GUI frameworks, document converters.

---

## 3. Abstract Factory Pattern

**Intent:** Provide an interface for creating families of related or dependent objects without specifying their concrete classes.

**Motivation:** System should be independent of how its products are created and composed; products from one family are designed to work together.

**Structure (UML):**

```
+--------------------+      +--------------------+
| AbstractFactory    |      | AbstractProductA   |
+--------------------+      +--------------------+
| +createA(): A      |      |                    |
| +createB(): B      |      +--------------------+
+--------------------+                ^
         ^                             |
         |                +--------------------+
+--------------------+   | ConcreteProductA1  |
| ConcreteFactory1   |   +--------------------+
+--------------------+                
```

**Implementation (Java):**

```java
public interface GUIFactory {
    Button createButton();
    Checkbox createCheckbox();
}

public class WinFactory implements GUIFactory {
    public Button createButton() { return new WinButton(); }
    public Checkbox createCheckbox() { return new WinCheckbox(); }
}
```

**Pros:**

- Ensures compatibility among products.
- Promotes consistency across products.

**Cons:**

- Difficult to support new kinds of products.
- Complexity increases with product families.

**Use Cases:** Cross-platform UI toolkits, database driver families.

---

## 4. Builder Pattern

**Intent:** Separate the construction of a complex object from its representation, allowing the same construction process to create different representations.

**Motivation:** Useful when creating complex objects step by step; hides internal representation.

**Structure (UML):**

```
+-----------+     +---------+
| Director  |<>---| Builder |
+-----------+     +---------+
| +construct()|   | +buildPartA()|
+-----------+     | +buildPartB()|
                  | +getResult()|
                  +---------+
```

**Implementation (Java):**

```java
public class MealDirector {
    public Meal prepareVegMeal(Builder builder) {
        builder.buildDrink();
        builder.buildMain();
        return builder.getMeal();
    }
}
```

**Pros:**

- Greater control over object construction.
- Clear separation between construction and representation.

**Cons:**

- Builder code can be verbose.
- Complexity increases with product variation.

**Use Cases:** Building complex objects like documents, parsers, and UI components.

---

## 5. Prototype Pattern

**Intent:** Specify the kinds of objects to create using a prototypical instance, and create new objects by copying this prototype.

**Motivation:** When the cost of creating a new object is expensive or complex, cloning a prototype can be more efficient.

**Structure (UML):**

```
+-------------+
| Prototype   |
+-------------+
| +clone():Self|
+-------------+
        ^
        |
+-------------+
| ConcreteProto|
+-------------+
```

**Implementation (Java):**

```java
public class Shape implements Cloneable {
    public Shape clone() throws CloneNotSupportedException {
        return (Shape) super.clone();
    }
}
```

**Pros:**

- Hides complexities of object creation.
- Reduces subclassing.

**Cons:**

- Cloning can be complex if the object graph is deep.
- Requires careful handling of mutable state.

**Use Cases:** Graphic editors, object caching, runtime configuration.

---

## Comparison Table

| Pattern          | Purpose                    | Complexity | Use Case Examples             |
| ---------------- | -------------------------- | ---------- | ----------------------------- |
| Singleton        | Single instance            | Low        | Logger, Config                |
| Factory Method   | Delegate instantiation     | Medium     | Dialogs, Parsers              |
| Abstract Factory | Family of related products | High       | UI Toolkits, Database Drivers |
| Builder          | Step-by-step construction  | Medium     | Document Builders, Meals      |
| Prototype        | Clone existing instances   | Medium     | Graphics, Caching             |

---

## When to Use Creational Patterns

- **Singleton:** When exactly one instance is needed.
- **Factory Method:** When a class cannot anticipate the type of objects it needs to create.
- **Abstract Factory:** When families of related products must be used together.
- **Builder:** When constructing a complex object step by step.
- **Prototype:** When object creation is expensive or complex.

---

## References

1. Gamma, E., Helm, R., Johnson, R., & Vlissides, J. (1994). *Design Patterns: Elements of Reusable Object-Oriented Software*.
2. Freeman, E., & Robson, E. (2004). *Head First Design Patterns*.

