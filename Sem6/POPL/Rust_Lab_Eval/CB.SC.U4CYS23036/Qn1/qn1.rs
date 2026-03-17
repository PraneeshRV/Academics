//Create a rust program that simulates a university course registration system. Define a struct Course containing the course code, maximum capacity, and number of students already enrolled. Create an enum Enrollment Status with Enrolled, Waitlisted and Dropped, Implement a trait Register with a method enroll() that allows a student to enroll in a course. If the number of enrolled students is less than capacity, the student shd be enrolled, else, the student should be placed in a waitlist

struct Course{
    course_code:String,
    maximum_capacity:i32,
    already_enrolled:i32
}

#[derive(Debug)]
enum EnrollmentStatus{
    Enrolled,
    Waitlisted,
    Dropped
}

struct Student{
    name:String,
    courses_registered:Vec<(String, EnrollmentStatus)>
}

trait Register {
    fn enroll(&mut self, student: &mut Student);
}

impl Register for Course{
    fn enroll(&mut self, student: &mut Student){
        if self.maximum_capacity > self.already_enrolled {
            self.already_enrolled += 1;
            student.courses_registered.push((self.course_code.clone(), EnrollmentStatus::Enrolled));
        }
        else {
            student.courses_registered.push((self.course_code.clone(), EnrollmentStatus::Waitlisted));
        }
    }
}

fn main(){
    let mut student1 = Student{
        name: "Praneesh R V".to_string(),
        courses_registered: Vec::new()
    };
    let mut course1 = Course {
        course_code: "20CYS312".to_string(),
        maximum_capacity: 59,
        already_enrolled: 50
    };
    let mut course2 = Course {
        course_code: "20CYS313".to_string(),
        maximum_capacity: 50,
        already_enrolled: 50
    };

    course1.enroll(&mut student1);
    course2.enroll(&mut student1);
    for (code, status) in &student1.courses_registered {
        println!("{} is enrolled in {} with status {:?}", student1.name, code, status);
    }
}