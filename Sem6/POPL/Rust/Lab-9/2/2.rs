use std::collections::{HashMap, HashSet};
use std::fs::File;
use std::io::{self, BufRead, BufReader, Write};
use std::str::FromStr;

#[derive(Debug, PartialEq, Eq, Hash, Clone)]
enum ActionType {
    LOGIN,
    DOWNLOAD,
    UPLOAD,
}

#[derive(Debug, PartialEq, Eq, Clone)]
enum StatusType {
    SUCCESS,
    FAIL,
}

#[derive(Debug)]
struct LogEntry {
    timestamp: String,
    ip: String,
    action: ActionType,
    status: StatusType,
}

#[derive(Debug)]
enum LogError {
    Io(io::Error),
    InvalidFormat(String),
    UnknownAction(String),
    UnknownStatus(String),
}

impl From<io::Error> for LogError {
    fn from(err: io::Error) -> Self {
        LogError::Io(err)
    }
}

impl FromStr for ActionType {
    type Err = LogError;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        match s {
            "LOGIN" => Ok(ActionType::LOGIN),
            "DOWNLOAD" => Ok(ActionType::DOWNLOAD),
            "UPLOAD" => Ok(ActionType::UPLOAD),
            _ => Err(LogError::UnknownAction(s.to_string())),
        }
    }
}

impl FromStr for StatusType {
    type Err = LogError;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        match s {
            "SUCCESS" => Ok(StatusType::SUCCESS),
            "FAIL" => Ok(StatusType::FAIL),
            _ => Err(LogError::UnknownStatus(s.to_string())),
        }
    }
}

fn parse_line(line: &str) -> Result<LogEntry, LogError> {
    let parts: Vec<&str> = line.split('|').collect();
    if parts.len() != 4 {
        return Err(LogError::InvalidFormat(format!("Line should have 4 parts separated by '|', found {}", parts.len())));
    }

    let timestamp = parts[0].to_string();
    let ip = parts[1].to_string();
    let action = ActionType::from_str(parts[2])?;
    let status = StatusType::from_str(parts[3])?;

    Ok(LogEntry {
        timestamp,
        ip,
        action,
        status,
    })
}

fn main() -> io::Result<()> {
    let input_path = "access.log";
    let corrupted_path = "corrupted_lines.txt";
    let report_path = "threat_report.txt";

    let file = File::open(input_path)?;
    let reader = BufReader::new(file);

    let mut corrupted_file = File::create(corrupted_path)?;
    let mut entries: Vec<LogEntry> = Vec::new();

    for line_result in reader.lines() {
        let line = line_result?;
        match parse_line(&line) {
            Ok(entry) => entries.push(entry),
            Err(e) => {
                let err_msg = match e {
                    LogError::Io(err) => format!("IO Error: {}", err),
                    LogError::InvalidFormat(msg) => format!("Invalid Format: {}", msg),
                    LogError::UnknownAction(act) => format!("Unknown Action: {}", act),
                    LogError::UnknownStatus(stat) => format!("Unknown Status: {}", stat),
                };
                writeln!(corrupted_file, "Line: '{}' | Error: {}", line, err_msg)?;
            }
        }
    }

    // Analysis
    let mut login_failures: HashMap<String, i32> = HashMap::new();
    let mut total_failures: HashMap<String, i32> = HashMap::new();
    let mut ip_actions: HashMap<String, HashSet<ActionType>> = HashMap::new();

    for entry in &entries {
        // Track total failures for reporting context
        if entry.status == StatusType::FAIL {
            *total_failures.entry(entry.ip.clone()).or_insert(0) += 1;
        }

        // Track specific login failures
        if entry.action == ActionType::LOGIN && entry.status == StatusType::FAIL {
            *login_failures.entry(entry.ip.clone()).or_insert(0) += 1;
        }

        // Track actions for suspicious pattern detection
        ip_actions
            .entry(entry.ip.clone())
            .or_insert_with(HashSet::new)
            .insert(entry.action.clone());
    }

    let mut report_file = File::create(report_path)?;
    writeln!(report_file, "Suspicious Activity Report")?;
    writeln!(report_file, "==========================")?;

    // Collect all unique IPs encountered
    let all_ips: HashSet<&String> = ip_actions.keys().chain(login_failures.keys()).collect();
    let mut reported_ips: HashSet<&String> = HashSet::new(); // to avoid duplicates if analyzed differently

    for ip in all_ips {
        if reported_ips.contains(ip) {
            continue;
        }

        let mut reasons = Vec::new();
        let fail_count = *total_failures.get(ip).unwrap_or(&0);
        let login_fail_count = *login_failures.get(ip).unwrap_or(&0);

        // Check: > 3 failed logins
        if login_fail_count > 3 {
            reasons.push(format!("Excessive failed logins ({})", login_fail_count));
        }

        // Check: UPLOAD and DOWNLOAD in same session
        if let Some(actions) = ip_actions.get(ip) {
            if actions.contains(&ActionType::UPLOAD) && actions.contains(&ActionType::DOWNLOAD) {
                reasons.push("Performed both UPLOAD and DOWNLOAD".to_string());
            }
        }

        if !reasons.is_empty() {
            writeln!(
                report_file,
                "IP: {} | Failures: {} | Reason: {}",
                ip,
                fail_count,
                reasons.join(", ")
            )?;
            reported_ips.insert(ip);
        }
    }

    println!("Analysis complete. Check {} and {}", corrupted_path, report_path);
    Ok(())
}
