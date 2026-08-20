# Unit 1 — Biometric Fundamentals and Standards

Source: `1a_ Biometric fundamentals.pdf`, `1b_ Performance metrics _ Biometric Standards.pdf`.

---

## 1. What biometrics is

**Biometrics** is the science of establishing the identity of an individual based on the
**physical, chemical or behavioral attributes** of the person. Biometric technologies are
*automated* methods of verifying or recognising the identity of a **living** person from a
physiological or behavioral characteristic.

A **biometric** is a characteristic of a human being that can distinguish one person from
another, used for **identification** or **verification** of identity.

| Physiological — related to the shape of the body | Behavioral — related to the behavior of a person |
|---|---|
| Fingerprint, face recognition, DNA, palm print, hand geometry, iris recognition | Voice, signature, typing pattern |

---

## 2. Why biometrics — against the traditional schemes

Before biometrics, automatic identification had two families:

| Family | Basis | Examples | Failure mode |
|---|---|---|---|
| Knowledge-based | "something you **know**" | Password, PIN | Forgotten or guessed |
| Token-based | "something you **have**" | Credit card, smart card, keys | Lost, stolen or forgotten (≈25% of people write the PIN on the card) |

**The core defect:** neither approach can differentiate an authorised person from an impostor
who holds the credential. Biometrics moves the basis to **"who you are"** or **"what you do"**.

Annual identity-fraud damage figures quoted in the slides: $1 bn welfare disbursements,
$1 bn credit card transactions, $1 bn fraudulent cellular phone use, $3 bn ATM withdrawals.

### Benefits versus traditional authentication

1. **Increased security** — resources are reachable only by authorised users. Passwords and PINs
   are easily guessed or compromised and tokens can be stolen; biometric data cannot be guessed
   or stolen in the same fashion.
2. **Increased convenience** — passwords are kept simple *because* they are easily forgotten.
   Biometrics are difficult or impossible to forget, so highly sensitive information can more
   readily be exposed on a biometrically protected network than a password-protected one.
3. **Increased accountability** — strong auditing and reporting. Biometric access control
   eliminates **buddy-punching** and gives high certainty about *which user accessed which
   machine at what time*. Even rarely-used audit capability works as a deterrent.

---

## 3. Operation of a biometric system

A biometric system is essentially a **pattern-recognition system**: it acquires biometric data
from an individual, extracts a salient feature set, compares that feature set against the stored
feature set(s), and takes an action based on the comparison.

### The four modules

**(a) Sensor module.** A suitable reader or scanner acquires the raw biometric data — for
example an optical fingerprint sensor imaging the friction-ridge structure of the fingertip.
The sensor module **defines the human–machine interface** and is therefore *pivotal to the
performance of the system*: a poorly designed interface produces a high **failure-to-acquire**
rate and consequently low user acceptability.

**(b) Quality assessment and feature extraction module.** Quality of the acquired data is
assessed first to decide whether it is fit for further processing. The data is typically passed
through a **signal enhancement** algorithm; if quality is still too poor the user is asked to
present the biometric again. The data is then processed and a set of **salient discriminatory
features** is extracted — e.g. the *position and orientation of minutiae points* (local ridge and
valley anomalies) in a fingerprint. During enrolment this feature set is stored in the database
and is called a **template**.

**(c) Matching and decision-making module.** Extracted features are compared against stored
templates to generate **match scores**. The score may be **moderated by the quality** of the
presented data. The embedded decision-making module uses the scores either to validate a claimed
identity (verification) or to rank the enrolled identities (identification).

**(d) System database module.** Stores the enrolment templates.

### How the technology works, physically

Acquisition devices — cameras, scanners — capture images, recordings or measurements of the
individual's characteristics; computer hardware and software then **extract, encode, store and
compare** them.

---

## 4. Biometric characteristics — the seven properties

1. **Universality** — every individual accessing the application should possess the trait.
2. **Uniqueness** — the trait should be sufficiently different across the population.
3. **Permanence** — sufficiently invariant over time *with respect to the matching algorithm*.
   A trait that changes significantly over time is not a useful biometric.
4. **Measurability** — acquirable and digitisable with devices that do not cause undue
   inconvenience, and the raw data must be amenable to feature extraction.
5. **Performance** — recognition accuracy and the resources needed to reach it must satisfy the
   constraints imposed by the application.
6. **Acceptability** — the target population must be willing to present the trait.
7. **Circumvention** — the ease with which the trait can be imitated: **artifacts** (fake
   fingers) for physical traits, **mimicry** for behavioral traits.

---

## 5. The two stages: enrolment, then verification or identification

### Enrolment

The process by which a user's biometric data is initially acquired, assessed, processed and
stored as a template for ongoing use.

- The person first provides an **identifier** such as an identity card; the biometric is **linked
  to the identity** on that document.
- Distinctive features are located, one or more samples are extracted, encoded and stored as a
  **reference template**.
- Template size varies by vendor and technology. Templates are stored **remotely in a central
  database** or **within the reader device itself**.
- Enrolment occurs in **both 1:1 and 1:N systems**, and **quality enrolment is critical to
  long-term accuracy** — low-quality enrolments cause high false match *and* false non-match
  rates.
- Because biometric features change over time, people may have to **re-enrol** to refresh the
  reference template.

### Supporting vocabulary

- **Presentation** — the act of providing biometric data to the acquisition device: looking at a
  camera, placing a finger on a **platen**, reciting a passphrase; possibly removing eyeglasses
  or staying still for several seconds.
- **Biometric data / raw biometric data / biometric sample** — the unprocessed image or
  recording. **Raw biometric data cannot be used to perform matches**; systems do not store it,
  they use it for template creation. Some systems need several presentations to enrol — finger-scan
  systems typically capture each finger two to four times, and may enrol multiple fingers (or
  irises, or retinas) to create multiple enrolment templates.
- **Feature extraction** — the automated process of locating and encoding distinctive
  characteristics from biometric data to generate a template. It runs at **enrolment and at every
  verification** — any time a template is created. It includes filtering and optimisation of
  images and data. Its quality directly bounds system performance.
- **Template** — a small file derived from the distinctive features, used to perform matches.
  **Systems store and compare templates, not biometric data.**
  - **Enrolment templates** — created at the user's initial interaction, stored for future
    comparisons.
  - **Match templates** — generated during a verification or identification attempt, compared
    against the stored template, and **generally discarded immediately afterwards**.

### Verification (1:1)

The system validates a person's identity by comparing the captured biometric data with **that
person's own** stored template(s). Also called authentication. Used for **positive recognition**,
whose aim is to **prevent multiple people from using the same identity**.

### Identification (1:N)

The system recognises an individual by searching the templates of **all** users for a match — a
one-to-many comparison. It is critical for **negative recognition**, where the system establishes
whether a person is who they (implicitly or explicitly) **deny** being; the purpose is to
**prevent a single person from using multiple identities**. Identification is also used for
positive recognition purely for convenience.

### When each is appropriate

- PC and network security generally use **verification**.
- Building and room access can use either, but **verification predominates**.
- Large-scale public benefits programmes generally use **identification**.

### Verification vs identification — the comparison

- Verification systems are **faster and more accurate**: instead of hundreds of comparisons they
  match a person against their own data, needing less compute and lowering the chance of matching
  an unauthorised user. Nearly all verification systems decide in **under one second**.
- Verification **cannot** determine whether a person appears in the database more than once.
- Identification needs far more computational power — in some cases millions of comparisons
  before a match — and is deployed when verification simply does not make sense, e.g. eliminating
  duplicate enrolments. On the desktop, the loss of speed and accuracy outweighs the modest
  benefit of dropping a username.

---

## 6. Biometric matching, scoring, threshold, decision

**Matching** is the comparison of biometric templates to determine their degree of similarity or
correlation. The verification template created at the attempt is matched against the enrolment
template(s) — a user may have more than one enrolled.

**Scoring.** The result is a **score**, a number indicating degree of similarity. There is **no
standard scale**: some systems use 1–100, others −1 to 1; scores may be logarithmic or linear and
carried to several decimal places. Scales vary by technology *and* by vendor.

**Threshold.** A predefined number, generally chosen by the **system administrator**, that
establishes the degree of correlation required for a comparison to count as a match. Thresholds
can vary **from user to user, transaction to transaction, and attempt to attempt**. Systems can
be highly secure or not secure at all purely as a function of threshold setting.

**Decision.** The result of comparing score against threshold: **match, non-match, or
inconclusive**, with varying degrees of strong match and non-match possible.

**The whole matching sequence in six lines:** enrol → template stored → user presents data →
match template created → compared with one or more enrolment templates → score compared to
threshold → match / no-match transmitted.

---

## 7. Performance measures

### False Match Rate (FMR) = False Acceptance Rate (FAR)

The probability that a user's template will be **incorrectly judged to be a match for a different
user's template**. It happens because two people have similar enough characteristics. FMR is
lowered by adjusting the threshold to demand more correlation. The name FAR assumes the
consequence of a successful match is *acceptance* into a building, application or resource —
usually true.

**FMR and FNMR are inversely related and must always be assessed together.** A system with a 0%
FMR but a 50% FNMR is **secure but unusable**.

**When false matches are acceptable** — casino surveillance for known card counters. Without
biometrics, staff must memorise every card counter's face and inspect every face at every
blackjack table. With facial-scan, software scans the security-camera feed, locates faces and
performs rapid 1:N identification against the card-counter database, flagging anything close for
a human to adjudicate. **Even if 9 out of 10 flags are wrong**, the system is valuable because it
collapses the manual effort.

**Large-scale identification** needs much lower FMR than verification does, because over a
billion comparisons may occur in a day. **Negative identification** systems — those ensuring an
individual's data is not present more than once — require especially low FMR.

### False Non-Match Rate (FNMR) = False Rejection Rate (FRR)

The probability that a user's template is **incorrectly judged not to match their own enrolment
template**; in practice, an authorised user locked out. It occurs when the correlation between
the verification and enrolment templates is not strong enough. Three causes:

1. **Changes in the user's biometric data.** Voice-scan degrades with a sore throat; facial-scan
   degrades after drastic changes in facial hair or weight; even fingerprints change through
   scars, ageing and wear. **Most susceptible:** facial-scan and hand-scan. **Least susceptible:**
   iris-scan and retinal scan. Finger-scan robustness varies too widely across vendors to
   generalise.
2. **Changes in user presentation.** Even with unchanged data, *how* the user presents can cause
   substantial false rejection, and this is not necessarily carelessness — finger-scan systems
   advise moving the finger up or down, voice-scan systems advise speaking louder or softer.
   **Behavioral biometrics are especially subject to presentation change.**
3. **Changes in environment.** Variations in background lighting and composition, noise, even
   temperature. Example: enrolling on a **landline** and verifying via **mobile phone** is likely
   to produce high FNMR.

### Failure-to-Enroll (FTE) Rate

The probability that a given user will be **unable to enrol at all**. Causes: insufficiently
distinctive or replicable biometric data, or a solution design that makes consistent data hard to
provide. High FTE is particularly problematic because users who cannot enrol must fall back to a
different biometric or a different authentication method entirely.

**Relation to FNMR:** loosening enrolment settings — reducing the number of distinctive or
replicable features required — lowers FTE by letting marginal images and data enrol, but this
pushes FNMR up.

### Derived metrics

- **Equal Error Rate (EER)**, also called the **crossover rate**: the rate at which FNMR equals
  FMR. It represents the accuracy level at which a false match is as likely as a false non-match,
  and is commonly used as a single indicator of overall accuracy — resistance to break-ins
  combined with ability to match genuine users.
  **Two limitations:** it is generated from a single FMR/FNMR pair, neither of which reflects
  real-world operation; and **it does not incorporate FTE** — a system can show an extremely low
  EER alongside a 15% failure-to-enroll rate.
- **Ability-to-Verify (ATV) Rate** — a more valuable derived metric: a combination of FTE and
  FNMR indicating the overall percentage of users who will be **capable of authenticating on a
  daily basis**.

---

## 8. Privacy risks of biometrics

Unlike passwords, biometric traits are **permanent and difficult to change**. If compromised, an
individual cannot replace a fingerprint or an iris.

1. **Irrevocability risk** — passwords can be changed if leaked; biometric traits cannot. Stolen
   biometric data creates lifelong identity risk. *Example:* a breached fingerprint database lets
   attackers spoof other systems.
2. **Unauthorised tracking and surveillance** — biometric systems can identify people without
   their knowledge: face recognition cameras in public spaces, tracking movement across malls,
   airports, cities. The concern is **loss of anonymity**.
3. **Function creep** — data collected for one purpose is later used for another. *Example:* a
   university collects facial data for attendance, then reuses it to monitor student behaviour.
4. **Data breaches** — biometric databases are attractive targets; consequences are identity
   theft, account compromise and fraudulent authentication.
5. **Profiling and discrimination** — biometric data may reveal age, gender, ethnicity and health
   conditions, enabling unfair decision-making.
6. **Spoofing and presentation attacks** — fake fingerprints, deepfake faces, recorded voices used
   to bypass authentication.

### Privacy Impact Assessment (PIA) for biometrics

| Question | Assessment |
|---|---|
| What biometric data is collected? | Fingerprint, face, iris |
| Why is it collected? | Authentication |
| Who can access it? | Admin, vendor |
| Where is it stored? | Local server / cloud |
| How long is it retained? | Defined retention period |
| What happens after deletion? | Secure erasure |
| What are the risks? | Leakage, surveillance |

### Designing privacy-sympathetic biometric systems

A privacy-sympathetic system protects users while still providing authentication.

- **Principle 1 — Data minimisation:** collect only the necessary biometric information.
- **Principle 2 — Template protection:** store *transformed* templates instead of raw images.
  Techniques: **hashing, cancellable biometrics, bio-cryptography**. Benefit: even if stolen, the
  original trait cannot easily be reconstructed.
- **Principle 3 — Encryption, user consent and transparency.**
- **Decentralised storage.**

---

## 9. Biometric standards

**Definitions.** ISO/IEC Guide 2:2004: a standard is "a document, established by consensus, that
provides rules, guidelines or characteristics for activities or their results." The Biometric
Consortium: "a general set of rules to which all complying procedures, products or research must
adhere." Standards establish the size, configuration or protocol of a product, process or system,
specify performance of products or personnel, and **define terms so there is no misunderstanding
among those using the standard**. Standards for collection, storage and sharing of biometric data
matter greatly to both government and private systems.

### Bodies

**ISO / IEC** — International Organization for Standardization and International Electrotechnical
Commission. Responsibilities: biometric data formats, performance evaluation, security
requirements, privacy guidelines, testing methodologies. Examples: **ISO/IEC 19794**,
**ISO/IEC 24745**, **ISO/IEC 30107**.

**NIST** — National Institute of Standards and Technology. Develops biometric testing frameworks
and accuracy benchmarks, and runs the **Face Recognition Vendor Tests (FRVT)** and the
**Fingerprint Vendor Technology Evaluation (FpVTE)**. Contribution: evaluates biometric
algorithms and publishes performance benchmarks.

### The four categories of standard

**Technical interfaces** — specify interfaces and interactions between biometric components and
subsystems, including possible security mechanisms protecting stored data and data transferred
between systems.
*Examples:* ANSI INCITS 358-2002 **BioAPI Specification v1.1**; ANSI INCITS 398-2005
[NISTIR 6529-A] **Common Biometric Exchange File Format (CBEFF)**.

**Data interchange formats** —
*Examples:* ANSI INCITS 377-2004 Finger Pattern Based Interchange Format; ANSI INCITS 378-2004
Finger Minutiae Format for Data Interchange; ANSI INCITS 379-2004 Iris Image Interchange Format.

**Application profile standards** —
*Examples:* ANSI INCITS 383-2003 Biometrics-Based Verification and Identification of
Transportation Workers; ANSI INCITS 394-2004 Data Interchange and Data Integrity of
Biometric-Based Personal Identification for Border Management.

**Performance testing and reporting** —
*Examples:* ANSI INCITS 409.1-2005 Part 1 — Principles Framework; 409.2-2005 Part 2 — Technology
Testing Methodology; 409.3-2005 Part 3 — Scenario Testing Methodologies.

---

## 10. Application properties

The syllabus lists "application properties" as the closing topic of Unit 1. The standard set of
axes on which a biometric application is characterised — use them to justify a technology choice
in a design question:

| Property | The two poles | Why it matters |
|---|---|---|
| Cooperative vs non-cooperative | Does the user *want* to be recognised? | A non-cooperative impostor changes the threat model; watchlists are non-cooperative. |
| Overt vs covert | Is the user aware of the capture? | Covert capture drives the surveillance and consent objections. |
| Habituated vs non-habituated | Is the user a frequent user of the system? | Habituated users present consistently, so FNMR falls with use. |
| Attended vs unattended | Is an operator supervising the presentation? | An attendant deters spoofing and corrects bad presentation. |
| Standard vs non-standard environment | Controlled indoor vs open outdoor | Lighting, noise and temperature drive FNMR (§7). |
| Public vs private | General public vs employees | Employees can be compelled to enrol; the public cannot. |
| Open vs closed system | Are templates exchanged with other systems? | An open system *requires* data-interchange standards (§9). |
