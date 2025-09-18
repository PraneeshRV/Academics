
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class form extends JFrame {
    private JTextField nameField, rollField;
    private JComboBox<String> deptCombo;
    private JRadioButton maleButton, femaleButton;
    private JCheckBox readingBox, sportsBox, musicBox;
    private JTextArea displayArea;
    private ButtonGroup genderGroup;

    public form() {
        setTitle("Student Registration Form");
        setSize(500, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));

        // Name Field
        add(new JLabel("Name*: "));
        nameField = new JTextField(20);
        add(nameField);

        // Roll Number Field
        add(new JLabel("Roll Number*: "));
        rollField = new JTextField(20);
        add(rollField);

        // Department ComboBox
        add(new JLabel("Department*: "));
        String[] departments = {"Select Department", "Computer Science", "Electronics", "Mechanical", "Civil"};
        deptCombo = new JComboBox<>(departments);
        add(deptCombo);

        // Gender Radio Buttons
        add(new JLabel("Gender: "));
        genderGroup = new ButtonGroup();
        maleButton = new JRadioButton("Male");
        femaleButton = new JRadioButton("Female");
        genderGroup.add(maleButton);
        genderGroup.add(femaleButton);
        add(maleButton);
        add(femaleButton);

        // Hobbies Checkboxes
        add(new JLabel("Hobbies: "));
        readingBox = new JCheckBox("Reading");
        sportsBox = new JCheckBox("Sports");
        musicBox = new JCheckBox("Music");
        add(readingBox);
        add(sportsBox);
        add(musicBox);

        // Buttons
        JButton submitButton = new JButton("Submit");
        JButton clearButton = new JButton("Clear");
        add(submitButton);
        add(clearButton);

        // Display Area
        displayArea = new JTextArea(10, 40);
        displayArea.setEditable(false);
        add(new JScrollPane(displayArea));

        // Submit Button Action
        submitButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (validateFields()) {
                    StringBuilder result = new StringBuilder();
                    result.append("Student Details:\n\n");
                    result.append("Name: " + nameField.getText() + "\n");
                    result.append("Roll Number: " + rollField.getText() + "\n");
                    result.append("Department: " + deptCombo.getSelectedItem() + "\n");
                    
                    // Gender
                    String gender = maleButton.isSelected() ? "Male" : (femaleButton.isSelected() ? "Female" : "Not specified");
                    result.append("Gender: " + gender + "\n");
                    
                    // Hobbies
                    result.append("Hobbies: ");
                    if (readingBox.isSelected()) result.append("Reading ");
                    if (sportsBox.isSelected()) result.append("Sports ");
                    if (musicBox.isSelected()) result.append("Music ");
                    
                    displayArea.setText(result.toString());
                } else {
                    JOptionPane.showMessageDialog(form.this,
                        "Please fill all mandatory fields (Name, Roll Number, Department)",
                        "Error",
                        JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        // Clear Button Action
        clearButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                nameField.setText("");
                rollField.setText("");
                deptCombo.setSelectedIndex(0);
                genderGroup.clearSelection();
                readingBox.setSelected(false);
                sportsBox.setSelected(false);
                musicBox.setSelected(false);
                displayArea.setText("");
            }
        });

        setVisible(true);
    }

    private boolean validateFields() {
        return !nameField.getText().trim().isEmpty() &&
               !rollField.getText().trim().isEmpty() &&
               deptCombo.getSelectedIndex() != 0;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new form();
            }
        });
    }
}
