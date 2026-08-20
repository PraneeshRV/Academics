# Likely Exam Questions with Model Answers

Ranked by how strongly the source decks signal them. Answer skeletons are written at the length
the marks suggest — expand a 2-mark bullet into a sentence, a 10-mark skeleton into paragraphs.

---

## Tier 1 — near-certain

### Q1. Compare biometrics with traditional authentication techniques. (5–10 marks)

Structure the answer in three moves.

1. **The two traditional families and their defect.** Knowledge-based ("something you know" —
   password, PIN) fails by being forgotten or guessed; token-based ("something you have" — card,
   key fob) fails by being lost or stolen; roughly 25% of people write the PIN on the card. The
   defect they share is that **neither binds to a person** — they cannot distinguish an authorised
   user from an impostor holding the credential. Fraud figures: $3 bn ATM withdrawals, $1 bn each
   in welfare, credit card and cellular fraud annually.
2. **What biometrics changes.** Identity is established from **"who you are" or "what you do"** —
   physical, chemical or behavioral attributes of a **living** person.
3. **The three benefits, each with its mechanism:** increased **security** (cannot be guessed or
   stolen the way a password or token can), increased **convenience** (impossible to forget, so
   sensitive resources can be exposed more readily than under passwords), increased
   **accountability** (eliminates buddy-punching; gives certainty about who accessed what and
   when; audit capability deters even when unused).
4. **Closing balance** — biometrics is not strictly superior: traits are irrevocable, they have a
   non-zero FTE so some users cannot enrol at all, and they carry privacy risk that a password
   does not. The honest conclusion is that biometrics binds identity to a person, which the other
   two factors cannot do, at the cost of permanence.

### Q2. Explain the key biometric processes: verification, identification and matching. (10 marks)

Cover: the four modules (sensor / quality-assessment & feature-extraction / matching & decision /
database); the two stages (enrolment, then verification or identification); the enrolment
vocabulary (presentation, raw biometric sample, feature extraction, enrolment vs match template);
then the **1:1 vs 1:N table** from `00-CRAM-SHEET.md` §4; then the matching chain **score →
threshold → decision (match / non-match / inconclusive)**, noting that there is no standard
scoring scale and that the threshold is administrator-set and can vary per user, per transaction
and per attempt.

Highest-value single sentence: **verification supports positive recognition (stops many people
using one identity); identification supports negative recognition (stops one person using many
identities).**

### Q3. Explain the performance measures in biometric systems. (10 marks)

Define **FMR/FAR**, **FNMR/FRR**, **FTE**, then **EER** and **ATV**. You must state:

- FMR and FNMR are **inversely related** and are set by the threshold — a 0% FMR with 50% FNMR is
  secure but unusable.
- The **three causes of false non-matches**: changed biometric data, changed presentation, changed
  environment (landline enrolment → mobile verification).
- Loosening enrolment lowers FTE but raises FNMR.
- The **two criticisms of EER**: derived from a single FMR/FNMR pair, and it ignores FTE entirely.
- **ATV** = FTE + FNMR combined = the share of users who can actually authenticate day to day.

Draw the FMR/FNMR crossover curve with EER at the intersection and label the axes "threshold
loose → tight" and "error rate".

### Q4. PCA / Eigenfaces numerical. (10 marks)

Full method and both worked examples in `01-PCA-Worked-Problems.md`. Show every step: flatten →
mean face → normalise → covariance → eigen-decomposition → select top *k* → weights `w = vᵀφ` →
Euclidean distance → smallest distance wins. Reuse the **training** mean and eigenvectors on the
test face.

### Q5. Assess the privacy risks of biometrics and describe how to design a privacy-sympathetic system. (10 marks)

Six risks — irrevocability, unauthorised tracking/surveillance, function creep, data breach,
profiling and discrimination, spoofing — each with its example. Then the **PIA question table**.
Then the four design principles: data minimisation; **template protection** (hashing, cancellable
biometrics, bio-cryptography — a stolen template cannot be inverted); encryption, consent and
transparency; decentralised storage. Close with **FIDO2/WebAuthn** as the worked example of
decentralised storage in practice: the biometric never leaves the secure enclave and the server
receives only a signature.

---

## Tier 2 — very likely

### Q6. What are the desirable characteristics of a biometric trait?

Universality, uniqueness, permanence, measurability, performance, acceptability, circumvention —
with the one-line gloss each from `02-Unit1` §4. Add that no single trait scores well on all
seven, which is the argument for **multimodal biometrics**.

### Q7. Describe the different biometric standards.

Definitions (ISO/IEC Guide 2:2004 and the Biometric Consortium), the bodies (ISO/IEC with 19794 /
24745 / 30107; NIST with FRVT and FpVTE), then the **four categories** with one named example
each: technical interfaces (BioAPI, CBEFF), data interchange formats (INCITS 377/378/379),
application profiles (INCITS 383, 394), performance testing and reporting (INCITS 409.1/.2/.3).

### Q8. Explain the working of a finger-scan system, and the security threats at each stage.

Three sensor types → the five-stage pipeline → binarisation and thinning to one pixel → minutiae
(ridge ending, bifurcation) → false minutiae from scars, sweat, dirt must be discarded → template
holds coordinates, angle, type, quality → matching algorithms. Then the **stage-by-stage threat
table** and countermeasures, with **liveness detection** (multi-spectral, pulse, sweat pore,
temperature) as the answer to spoofing and **hill-climbing** as the matcher-stage threat worth
naming.

### Q9. Explain the working of a face biometric system. State its strengths and weaknesses.

Pipeline (acquisition → processing → distinctive characteristic location → template creation →
matching); 2D vs 3D/IR acquisition with the 30,000-dot Face ID example; the three image-processing
steps (crop, colour conversion, normalisation/alignment); ~80 nodal points → faceprint /
128-dimensional embedding; Haar cascades or CNNs for detection; Euclidean or cosine distance
against threshold. **Strengths:** leverages existing cameras, searches static images such as
licence photos, **the only biometric that works without user cooperation**. **Weaknesses:**
environment changes, physiological changes, privacy abuse potential — plus the demographic bias
where acquisition devices are not optimised for darker skin tones.

### Q10. Differentiate voice recognition from speech recognition. Explain how voice-scan works.

The WHO vs WHAT table, then the phone-banking illustration, then the point that voice-scan is
**both** physiological (vocal tract shape) and behavioral (what is said and how). Follow with
components (acquisition hardware + local/central software), the pipeline, the distinctive features
list (pitch, gain, short-time spectrum, formants, LPC, cepstral coefficients, spectrograms, nasal
coarticulation), **HMM** template creation, and speaker-dependent vs speaker-independent. Finish
with the four weaknesses, replay susceptibility first.

### Q11. Explain keystroke dynamics and signature-scan.

Keystroke: definition, **dwell time** and **flight time**, software-only so no extra hardware.
Signature: **static** (paper → scan → shape only) vs **dynamic** (tablet → shape, speed, stroke,
pen pressure, timing in real time) and why dynamic resists forgery — the forger reproduces the
artifact, not the process that made it.

### Q12. Compare physiological and behavioral biometrics.

The five-row table in `04-Unit3` §0: what is measured, capture mode, friction, revocability, best
role. Then the key asymmetry: physiological traits are **immutable, so they cannot be reissued
after compromise**; behavioral templates **drift, so they must be re-enrolled** — which makes them
weaker as a gate but usable as a **continuous risk signal**.

---

## Tier 3 — worth 10 minutes each

### Q13. Cognitive biometrics: ECG and EEG.

Definition (signals from thought processes reflecting mental and emotional states). EEG: collective
neuronal activity, scalp electrodes, **10–20 placement**, 0.5–1.0 kHz per channel, hundreds of MB;
recording chain electrodes → amplifiers with filters → A/D converter → recording device. ECG: the
three named advantages — **inherent liveness, high security (no counterfeiting technology exists),
combined information (identity + cardiac condition + emotional/physical state)** — plus the
counterpoint that the same combined information is a medical-privacy risk.

### Q14. Hand vascular geometry analysis.

Three imaging techniques (IR, NIRS, thermography), the three processing steps (preprocessing,
feature extraction of width/length/branching, CNN-based pattern recognition), optional 3D
reconstruction, then the four challenges (image quality, variability with age/temperature/activity,
ethical concerns, regulatory approval). Security point: the trait is **internal**, leaves no latent
trace, and needs a live warm hand.

### Q15. DNA and dental biometrics.

DNA: most reliable, **intrinsically digital, unchanged during life or after death**, used in
criminal investigation, forensics, paternity testing via polymorphism analysis — but not real-time
and heaviest privacy load. Dental: radiographs give tooth contours, relative positions, shapes of
dental work; **feature extraction** via anisotropic diffusion + Mixture of Gaussians; **matching**
in three steps — tooth-level shape registration combined by posterior probabilities, image
distances via post-mortem/ante-mortem tooth correspondences, then subject identification.

### Q16. Gesture recognition: approaches, taxonomy and stages.

Glove-based vs vision-based (appearance-based vs 3D model-based); the 3D kinematic model with
palm, five fingers, MCP/PIP/DIP joints, DoF, and the linear vs angular parameters; the comparison
table 2D vs 3D; static vs dynamic gestures with **preparation → stroke → retraction**; offline vs
online; the four stages and the three levels (detection, tracking, recognition); applications.

### Q17. Gait recognition.

Definition, video-based silhouette extraction and segmentation, contour detection, feature
extraction distinguishing one gait from another, and the sensor-based variant. Note the
security/privacy duality: works at a distance without cooperation.

### Q18. Knuckle biometric.

Emerging hand-based trait; **weighted median filter** with a threshold derived from the image
pixel range for denoising, then **variational approach** for knuckle-region extraction, selecting
optimal pixels with minimum deviation and resolving non-convexity.

### Q19. Explain iris scan and retina scan and contrast them. **[textbook fill]**

Iris — external coloured annulus, NIR illumination, unwrapped and Gabor-filtered into an
**IrisCode**, matched by **Hamming distance**, extremely stable and highly unique, used in
national-scale 1:N deduplication. Retina — internal blood-vessel pattern, eyepiece contact with
low-intensity IR, most accurate and hardest to spoof but **most intrusive and least accepted**,
and alterable by diabetes and glaucoma. Contrast on: what is imaged, distance from device,
intrusiveness, acceptability, health-inference risk.

### Q20. Write short notes on AFIS. **[textbook fill]**

Large-scale 1:N infrastructure; ten-print and latent inputs; classification into arch, tented
arch, loop, whorl to bin the search; minutiae matching returning a **ranked candidate list**;
final identification by a **human latent examiner**; standards dependence for interoperability.
Frame it as a triage tool, which is why a relatively loose FMR is acceptable.

---

## The two answers that earn marks anywhere

**"Systems store templates, not biometric data."** Raw samples exist only to create templates and
cannot be matched. This one sentence answers privacy, storage and matching sub-questions alike.

**"FMR and FNMR are inversely related, and the threshold is where the business decides."** Any
question about accuracy, security-versus-usability, or setting up a deployment can be anchored on
this.
