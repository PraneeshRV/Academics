# SSE Mid-Term Lab Exam — Cram Sheet

**Course:** Secure Software Engineering (20CYS401) · **Date:** Tue 11 Aug 2026 · **Marks:** 20
**Syllabus:** Lab 1 (Refactoring), Lab 3 (STRIDE threat modelling), Lab 4 (Requirements /
analysis modelling with UML)

Everything below is derived from the three lab exercise PDFs and your own submitted
solutions in this folder.

---

## 0. Exam-day playbook

| Step | Action |
|---|---|
| 1 | Read the whole question paper first. Note which of the three labs each task maps to. |
| 2 | Budget time by marks. If it is 20 marks across three labs, do not spend 40 minutes on one diagram. |
| 3 | Refactoring task: **run the tests first**, before touching anything. Baseline green = your proof. |
| 4 | Refactor in small steps, re-running tests after each. Never batch five changes then run. |
| 5 | Diagram tasks: get all elements on the canvas first, label second, prettify last (only if time remains). |
| 6 | Always label your name + roll number (CB.SC.U4CYS23036) on every submitted file. Lab 3 explicitly marks this. |
| 7 | Export what the paper asks for: PDF report, tool-generated report, and the project file (`.json` for Threat Dragon, `.drawio` for draw.io). |

**Tools already installed on this machine:** `threat-dragon` (pacman, `/opt/Threat-Dragon-ng`),
`pytest`, `python3`. draw.io is **not** installed locally — use <https://app.diagrams.net>
(works offline once loaded; choose "Device" storage). Prior `.drawio` files are in `~/Downloads`.

---

## 1. Lab 1 — Refactoring

### The Golden Rule (they will ask this)

> Refactoring = altering the **structure** of code **without changing its external
> behaviour**. Run the regression test suite after **every single step**. If tests turn
> red, you broke it.

Corollary they graded on last time: the code base is **intentionally vulnerable**. Fixing a
security bug is a *behaviour change*, so it is **out of scope**. Flag it in the report as a
separate bug ticket; do not "fix" it inside a refactoring task.

### Smell → technique table (memorise this)

| Code smell | Refactoring technique | One-line why |
|---|---|---|
| Magic number / magic string (`4`, `20`, `3`, `100`, hardcoded salt) | Replace Magic Number with Symbolic Constant | Literal carries business meaning but no name; change requires hunting by value |
| Complex inline boolean (`any(c.isupper() for c in pw)`) | Extract Variable (explaining variable) | Names the intent so the condition reads as English |
| Deeply nested `if` ("arrow code") | Replace Nested Conditional with Guard Clauses | Handle failure cases early and return; happy path stays un-indented |
| Duplicate code in two functions | Extract Method | Single point of truth; fix once, not twice |
| Long method (many responsibilities) | Extract Method / Decompose Conditional | Raises cohesion, makes sub-task unit-testable |
| Repeated conditional structure (`or`-chains of the same shape) | Consolidate Conditional Expression + data table (`any()`) | Separates *data* (patterns) from *control flow* (scan) |
| Commented-out code, unused import | Remove Dead Code | Version control already keeps history; noise misleads readers |
| Top-level script side effects | Move behind `if __name__ == "__main__":` | Module becomes importable and testable |
| Long parameter list | Introduce Parameter Object | Groups cohesive arguments into one concept |
| Bad name | Rename Variable / Method | Cheapest, highest-value refactoring |

### Canonical answer shape for "identify and refactor"

For **each** smell write exactly four things — this is the rubric:

1. **Snippet** (paste the offending lines)
2. **Why it is a smell** (impact on maintainability, not just "it's ugly")
3. **Technique name** (use the standard Fowler name)
4. **How** (refactored pseudo-code / snippet)

Close the answer with: *"Tests re-run after each step — all green, so external behaviour is
preserved per the Golden Rule."*

### Ready-made code patterns

```python
# 1. Symbolic constants
MIN_USERNAME_LENGTH = 4
MAX_USERNAME_LENGTH = 20
MAX_FAILED_ATTEMPTS = 3

# 2. Extract Method (kills duplication)
def is_valid_username(username):
    return MIN_USERNAME_LENGTH <= len(username) <= MAX_USERNAME_LENGTH

def generate_hash(value):
    return hashlib.md5((value + LEGACY_SALT).encode()).hexdigest()

# 3. Guard clauses replace nesting, plus explaining variables
def check_password_strength(password):
    if len(password) < MIN_PASSWORD_LENGTH:
        return "WEAK"
    has_upper = any(c.isupper() for c in password)
    if not has_upper:
        return "WEAK"
    has_digit = any(c.isdigit() for c in password)
    if not has_digit:
        return "MEDIUM"
    return "STRONG"

# 4. Data table replaces repeated or-chains (order preserved = behaviour preserved)
INJECTION_RULES = [
    (["SELECT", "DROP", "DELETE", "UPDATE", "INSERT"], "ERR_SQLI"),
    (["<script>", "alert(", "onerror"],                "ERR_XSS"),
    ([";", "&&", "||", "|", "rm -rf"],                 "ERR_CMD_INJ"),
]

def scan_value(val):
    for patterns, error_code in INJECTION_RULES:
        if any(p in val for p in patterns):
            return error_code
    return None
```

### Traps that cost marks

- **Reordering checks changes behaviour.** If SQLi is checked before XSS, keep that order —
  a value matching both must still return `ERR_SQLI`.
- **Loop variable used after the loop** (`val` after `for key in data:`): the check only
  inspects the *last* field, and an empty dict raises `NameError`. Correct move in a
  refactoring lab: **preserve it, comment it, flag it as a bug** — do not silently fix it.
- Do not rename anything the tests import by name.
- `hashlib.md5` + hardcoded salt = a real vulnerability, but out of scope. Say so explicitly.

### Verification line to quote

```bash
python3 -m pytest -q
```

---

## 2. Lab 3 — STRIDE Threat Modelling (OWASP Threat Dragon)

### DFD notation

| Element | Symbol | Example (PayCloud) |
|---|---|---|
| External entity / Actor | Rectangle | Employee, HR Admin |
| Process | Circle | Web Application (Node.js), Payroll API (Python) |
| Data store | Two parallel lines / open rectangle | PostgreSQL DB, AWS S3 bucket |
| Data flow | Arrow, labelled with **what** moves | "HTTPS / Login Credentials", "REST API / JWT", "Fetch PDF" |
| Trust boundary | Dashed box or dashed line | Internet → DMZ; DMZ → Internal network |

**Every data flow must be labelled** with the data it carries. Unlabelled arrows lose marks.

### STRIDE table (memorise: letter → property violated → typical control)

| Letter | Threat | Violates | Applies to | Standard mitigation |
|---|---|---|---|---|
| **S** | Spoofing | Authentication | External entity, Process | MFA, strong password policy, HTTPS, salted hashing (bcrypt), account lockout |
| **T** | Tampering | Integrity | Process, Data store, Data flow | TLS, JWT validation, server-side input validation, digital signatures, integrity checks |
| **R** | Repudiation | Non-repudiation | Process, Data store | Secure audit logs with timestamps + user ID + IP, tamper-proof log storage, log review |
| **I** | Information Disclosure | Confidentiality | Process, Data store, Data flow | Encryption at rest and in transit, least-privilege ACLs, secure S3 bucket policy, encrypted backups, data masking |
| **D** | Denial of Service | Availability | Process, Data store, Data flow | Rate limiting, WAF, autoscaling, traffic monitoring, IP blocking |
| **E** | Elevation of Privilege | Authorization | Process | RBAC, authorize on **every** API request, least privilege, security testing |

Memory hook for applicability: **external entities** get S and R only; **data flows** get T,
I, D (no authentication of a flow itself); **data stores** get T, I, D (+R if it holds logs);
**processes** get all six.

### Your PayCloud six (reuse verbatim, adapt nouns if the scenario changes)

| # | Type | Title | Description |
|---|---|---|---|
| 1 | Spoofing | User Authentication Spoofing | Attacker uses stolen employee/HR credentials to impersonate a legitimate user via the login page. |
| 2 | Tampering | Payroll Data Tampering | Attacker modifies payroll requests or API messages between Web App and Payroll API, causing unauthorized salary/payment changes. |
| 3 | Repudiation | Payroll Update Repudiation | HR admin denies performing a payroll update or payment because no reliable audit trail exists. |
| 4 | Information Disclosure | Sensitive Payroll Information Disclosure | Employee PII, salary records or PDF payslips in PostgreSQL/S3 exposed through insecure permissions or leakage. |
| 5 | Denial of Service | DoS Against Web Application | Attacker floods the Web App with login/API requests, exhausting resources and blocking legitimate users. |
| 6 | Elevation of Privilege | Unauthorized Privilege Escalation | A normal employee exploits weak authorization in the Payroll API to reach HR-admin functions. |

Each threat needs: **Title, Type, Status (Open / Mitigated / N/A), Severity, Description,
Mitigation** — and must be **anchored to a specific component or data flow** in the diagram.

### Threat Dragon click-path

1. Launch `threat-dragon`, choose local session → **Create new threat model**.
2. Fill **Title**, **Owner**, **High-level description**, set business criticality (High for
   PII/financial). Save.
3. **Add a new diagram** → type **STRIDE**.
4. Drag elements from the left palette: Actor, Process, Store, Flow, Trust boundary.
5. Click an element → right panel → **Add threat** → pick type, fill description + mitigation
   + status + severity → Apply.
6. **Report** menu → generate PDF. **File → Save** produces the `.json` project file.
7. Submit: your PDF documentation (with name + roll number), the Threat Dragon PDF report,
   and the `.json`.

Your previous model is at `Assignment 3/PayCloud.json` — open it if you need a starting shape.

---

## 3. Lab 4 — Requirements analysis & UML modelling

Tool: <https://app.diagrams.net>. Your prior files: `~/Downloads/Untitled Diagram.drawio`
(use case), `02_ClassDiagram.drawio`, `03_ActivityDiagram.drawio`, `04_SequenceDiagram.drawio`.

### Noun/verb extraction (how to attack any new scenario in 3 minutes)

- **Nouns** in the scenario → candidate **classes** / data stores / entities.
- **Verbs** → **use cases** (actor-facing) and **operations** (class methods).
- **Who initiates?** → **actors**. Anything outside the system that the system talks to
  (payment gateway, email service) → **external system actor**.
- **Ordering words** ("then", "once approved", "before") → **activity / sequence** flow.
- **Conditions** ("if errors", "if payment fails") → decision nodes / `alt` fragments.

### 3.1 Use Case Diagram

Notation: actors = stick figures outside the boundary; system boundary = labelled rectangle;
use cases = ovals inside. Relationships:

- **`<<include>>`** — mandatory sub-behaviour, always executed (e.g. every use case includes
  *Log In*). Arrow points **from** the base use case **to** the included one.
- **`<<extend>>`** — optional/conditional behaviour (e.g. *Correct & Re-upload Rejected Data*
  extends *Upload Payroll Data*). Arrow points **from** the extension **to** the base.
- **Generalization** — solid line, hollow triangle. `Employee` and `HR Administrator`
  generalize to abstract `User`.

PayCloud skeleton (yours):

- Actors: `User {abstract}` → `Employee`, `HR Administrator`, `Payroll Approver`;
  `<<external system>> Payment Gateway`.
- Use cases: Log In · View Payslip · Download Payslip · Upload Monthly Payroll Data ·
  Validate Payroll Data · Report Validation Errors · Approve Payroll Batch ·
  Generate Payslips · Process Salary Payment · Notify Employee ·
  Correct & Re-upload Rejected Data.
- `<<include>>`: Log In into the user-facing cases; Validate Payroll Data into Upload;
  Generate Payslips into Approve Payroll Batch.
- `<<extend>>`: Report Validation Errors extends Validate; Correct & Re-upload extends Upload.

### 3.2 Class Diagram

Three-compartment box: **Name / Attributes / Operations**. Visibility: `+` public,
`-` private, `#` protected. Format: `- name: Type`, `+ method(param: Type): ReturnType`.

Relationships:

| Relationship | Line | Meaning |
|---|---|---|
| Association | plain line, multiplicity at both ends | structural link |
| Aggregation | hollow diamond at the whole | "has-a", parts can live alone |
| Composition | filled diamond at the whole | "owns-a", parts die with the whole |
| Generalization | hollow triangle at the parent | inheritance |
| Dependency | dashed arrow, `<<uses>>` | transient use |

Multiplicities: `1`, `0..1`, `1..*`, `*`.

PayCloud skeleton (yours): `User` (+login(): boolean, +logout(): void) generalized by
`Employee` and `HRAdmin(-adminId, -companyId)`; `Company(-companyId, -name, -address,
+addEmployee(e))` **employs** `1..*` Employee; HRAdmin **uploads** `1..*` `PayrollBatch`;
PayrollBatch **contains** `1..*` `PayrollRecord(+calculateNetPay(): double)`; PayrollBatch
`<<validated by>>` `ValidationEngine(-rules: List<Rule>)`; PayrollRecord `<<generates>>`
`1..*` `Payslip(+generatePDF(): File, +sendNotification(): void)`; `Payment(+initiatePayment(),
+updateStatus(status))` `<<uses>>` `PaymentGateway(-gatewayId, -apiEndpoint)`.

### 3.3 Activity Diagram

Notation: filled circle = start; rounded rectangle = action; diamond = decision/merge
(**label every outgoing edge** with the guard: `[errors found]` / `[no errors]`); thick bar =
fork/join for parallel actions; bullseye = end. Use **swimlanes** (partitions) — the lab
expects them.

PayCloud swimlanes and flow (yours): **HR Administrator | System | Payment Gateway | Employee**

Login → Upload Payroll Data → Validate Payroll Data → `Errors Found?`
— *Yes* → Notify HR Admin of Errors → (loop back: corrects and re-submits) → Upload
— *No* → Approve Payroll → Generate Payslips → Send Payment Request → Process Payment →
`Payment Successful?`
— *Yes* → Send Payment Confirmation → Update Payslip Status to Paid → Notify Employee
(Payslip Ready) → Employee: Login → View Payslip → Download Payslip → end
— *No* → Log Payment Failure → Notify HR Admin of Payment Failure → end

### 3.4 Sequence Diagram

Notation: participants across the top with **dashed lifelines**; **activation bars** for
execution; solid arrow with filled head = synchronous call; dashed arrow = return;
`alt` / `opt` / `loop` combined fragments with guard conditions in `[ ]`. Number the messages.

PayCloud skeleton (yours): participants **HR Admin, PayCloud System, Validation Engine,
Payslip Generator, Payment Gateway, Employee**

1 `login(username, password)` → 2 `authenticationSuccess` → 3 `uploadPayrollData(file)` →
4 `validate(payrollData)` → 5 `validationResult` → **alt** `[errors found]` 6 return
validation errors / `[no errors]` 7 validation success → 8 `approvePayroll(batchId)` →
9 `generatePayslips(batch)` → 10 payslips created → 11 `processPayment(payslips)` →
12 `paymentConfirmation` → 13 `updatePayslipStatus(Paid)` → 14 `login(...)` (Employee) →
15 authenticationSuccess → 16 `viewPayslip(month, year)` → 17 payslip data →
18 `downloadPayslip(payslipId)` → 19 payslip PDF file

### Diagram marks are lost on

- Missing system boundary box in the use case diagram.
- `<<include>>` / `<<extend>>` arrow direction reversed.
- Missing multiplicities on class associations.
- Unlabelled decision branches in the activity diagram.
- Return messages drawn as solid instead of dashed in the sequence diagram.
- Diagram inconsistency: a class that appears in the sequence diagram but not the class
  diagram. Keep the four diagrams talking about the same nouns.

---

## 4. Likely viva / short-answer questions

1. What is refactoring, and what is the golden rule? *(Structure changes, behaviour does not;
   run tests after every step.)*
2. What is technical debt? *(Cost of future rework caused by choosing an easy option now;
   accrues "interest" as maintenance slows.)*
3. Why refactor if the code works? *(Maintainability, readability, lower defect rate, cheaper
   change — critical in Agile where code is touched constantly.)*
4. Difference between refactoring and rewriting / bug fixing? *(Refactoring never changes
   observable behaviour; bug fixing does, by definition.)*
5. What is a trust boundary? *(A line where the privilege level or trust of data changes —
   data crossing it must be validated/authenticated.)*
6. Why STRIDE and not just a checklist? *(Systematic per-element coverage of the six security
   properties, driven by the architecture rather than by memory.)*
7. Which STRIDE categories apply to a data flow? *(Tampering, Information Disclosure, Denial
   of Service.)*
8. STRIDE ↔ security property mapping. *(See the table in section 2.)*
9. `<<include>>` vs `<<extend>>`. *(Mandatory vs conditional; opposite arrow directions.)*
10. Aggregation vs composition. *(Hollow vs filled diamond; part survives the whole vs it
    does not.)*
11. Activity vs sequence diagram. *(Activity = workflow/control flow across roles; sequence =
    time-ordered message exchange between objects for one scenario.)*
12. Why model requirements before coding? *(Ambiguity in natural language is cheapest to fix
    at analysis time; diagrams expose missing actors, states, and error paths.)*
