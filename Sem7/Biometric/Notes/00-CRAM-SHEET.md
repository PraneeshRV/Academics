# 20CYS443 Biometrics & Security — 30-Minute Cram Sheet

Scope: Unit 1 (Fundamentals + Standards), Unit 2 (Physiological), Unit 3 (Behavioral).
Read this file top to bottom once. Everything else in `Notes/` is depth for the parts you blank on.

---

## 1. The one-line definitions

| Term | Definition |
|---|---|
| Biometrics | Science of establishing identity from physical, chemical or behavioral attributes of a person. |
| Physiological trait | Related to the **shape of the body** — fingerprint, face, iris, retina, DNA, palm, hand geometry. |
| Behavioral trait | Related to the **behavior** of a person — voice, signature, keystroke, gait, gesture. |
| Verification | 1:1 match against **the claimed identity's** template. "Are you who you say you are?" |
| Identification | 1:N search of the **whole database**. "Who are you?" |
| Template | Small file of extracted distinctive features. Systems store **templates, not raw biometric data**. |
| Score | Number expressing similarity between enrolment and match template. |
| Threshold | Admin-set cutoff; score ≥ threshold ⇒ match. |

**Three authentication factors:** something you *know* (password/PIN) → something you *have* (token/card) → **something you *are* / *do* (biometric)**. Biometrics exists because the first two do not bind to a *person*: tokens are lost/stolen, PINs are forgotten/guessed, and neither can tell an authorised user from an impostor holding their credential.

---

## 2. Seven characteristics of a biometric trait (guaranteed question)

Mnemonic: **U-U-P-M-P-A-C**

1. **Universality** — everyone using the application has the trait.
2. **Uniqueness** — sufficiently different across the population.
3. **Permanence** — sufficiently invariant over time *with respect to the matching algorithm*.
4. **Measurability** — acquirable and digitisable without undue inconvenience; raw data must be processable into features.
5. **Performance** — accuracy and required resources meet the application's constraints.
6. **Acceptability** — the target population is willing to present the trait.
7. **Circumvention** — ease with which the trait can be imitated (fake fingers for physical traits, mimicry for behavioral). **Low circumvention is good.**

---

## 3. Four modules of a biometric system

```
Sensor  →  Quality assessment & Feature extraction  →  Matching & Decision  →  System database
```

- **Sensor module** — reader/scanner acquiring raw data. *Defines the human–machine interface, so it is pivotal to performance;* a bad interface causes a high failure-to-acquire rate and low user acceptability.
- **Quality assessment & feature extraction** — quality checked first, signal enhanced, re-capture requested if too poor; then salient discriminatory features extracted (e.g. minutiae position + orientation in a fingerprint).
- **Matching & decision-making** — compares features against stored templates, produces a match score (which may be moderated by input quality), then decides: validate a claim (verification) or rank enrolled identities (identification).
- **System database** — stores the enrolment templates.

## 3b. The two stages, and the enrolment vocabulary

**Stage 1 Enrolment → Stage 2 Verification or Identification.**

- **Enrolment** — user presents an identifier (ID card), the biometric is linked to that identity, features are extracted, encoded and stored as a **reference template**. Templates live in a central database *or* inside the reader device. Quality of enrolment drives long-term accuracy; poor enrolment ⇒ high FMR *and* FNMR. Traits change, so users may need to **re-enrol**.
- **Presentation** — the act of giving biometric data to the acquisition device (look at camera, finger on platen, say passphrase).
- **Biometric data / sample** — the raw unprocessed image or recording. **Raw data cannot be matched**; it exists only to create a template.
- **Feature extraction** — automated locating and encoding of distinctive characteristics into a template. Happens at *every* template creation — enrolment and verification alike.
- **Enrolment template** vs **match (verification) template** — the second is created per attempt and usually **discarded immediately after the comparison**.
- **Decision** — match / non-match / inconclusive.

---

## 4. Verification vs Identification (compare-and-contrast question)

| | Verification (1:1) | Identification (1:N) |
|---|---|---|
| Question | "Is this person who they claim?" | "Who is this person?" |
| Comparisons | One (or a few) | Whole database — possibly millions |
| Speed / cost | Fast, < 1 second, low compute | Slow, high compute |
| Accuracy | Higher | Lower (more chances to collide) |
| Recognition type | **Positive** recognition — stops many people using one identity | Critical for **negative** recognition — stops one person using many identities |
| Typical use | PC/network login, room access | Large-scale public benefits, de-duplication, watchlist surveillance |
| Limitation | Cannot detect a person enrolled twice | Reduced speed and accuracy make it overkill on the desktop |

---

## 5. Performance measures (numerical + theory question)

**Primary metrics**

- **FMR — False Match Rate**: probability a user's template is wrongly judged to match a *different* user's template. Also called **FAR (False Acceptance Rate)**. This is the **security failure**.
- **FNMR — False Non-Match Rate**: probability a user's template is wrongly judged *not* to match their own enrolment template. Also called **FRR (False Rejection Rate)**. This is the **usability failure** — the legitimate user is locked out.
- **FTE — Failure-to-Enroll Rate**: probability a user cannot enrol at all, because their data is insufficiently distinctive or replicable, or the solution makes consistent presentation hard. Users who cannot enrol need a fallback method, so a high FTE is a serious system problem.

**Derived metrics**

- **EER — Equal Error Rate** (a.k.a. crossover rate): the operating point where **FNMR = FMR**. Common single-number summary of accuracy. *Two criticisms to write down:* it is derived from a single FMR/FNMR pair which does not reflect real-world operation, and **it ignores FTE entirely** — a system can have a beautiful EER and a 15% FTE.
- **ATV — Ability-to-Verify Rate**: combines FTE and FNMR; gives the percentage of users who can actually authenticate on a daily basis. More operationally useful than EER.

**The trade-off sentence to write:** FMR and FNMR are **inversely related** — tightening the threshold lowers FMR and raises FNMR, and vice versa. A system with 0% FMR and 50% FNMR is *secure but unusable*. Loosening enrolment requirements lowers FTE but raises FNMR (marginal images get enrolled).

**Three causes of false non-matches:** (a) change in the user's biometric data (sore throat for voice, facial hair/weight for face, scars and ageing for fingerprint); (b) change in how the user presents (finger placement, speaking volume — behavioral traits suffer most); (c) change in the environment (lighting, background, noise, temperature — e.g. enrol on a landline, verify on a mobile ⇒ high FNMR). Eye-based traits (iris, retina) are *least* susceptible to (a).

**When are false matches acceptable?** Casino card-counter surveillance: facial-scan does 1:N against a watchlist and flags anything close; even if 9 of 10 flags are wrong, it has replaced staff memorising every face at every table. In **large-scale identification**, especially negative identification (proving someone is *not* already in the database), a billion comparisons a day forces a *much* lower FMR than any verification system would need.

---

## 6. Privacy risks + privacy-sympathetic design (essay question)

**Six risks**

1. **Irrevocability** — a leaked password is changed; a leaked fingerprint is not. Lifelong exposure.
2. **Unauthorised tracking / surveillance** — face recognition identifies without knowledge or consent; loss of anonymity.
3. **Function creep** — data collected for attendance later used to monitor behaviour.
4. **Data breach** — biometric databases are high-value targets; identity theft, fraudulent authentication.
5. **Profiling and discrimination** — traits can leak age, gender, ethnicity, health, enabling unfair decisions.
6. **Spoofing / presentation attacks** — fake fingerprints, deepfake faces, recorded voices.

**Privacy Impact Assessment (PIA) questions:** What data is collected? Why? Who can access it? Where is it stored? How long is it retained? What happens on deletion? What are the risks?

**Design principles for a privacy-sympathetic system**

1. **Data minimisation** — collect only what is needed.
2. **Template protection** — store transformed templates, never raw images. Techniques: **hashing, cancellable biometrics, bio-cryptography**. Benefit: a stolen template cannot be inverted back to the original trait.
3. **Encryption, user consent, transparency.**
4. **Decentralised storage** — keep the template on the user's device (see FIDO2 below) rather than a central honeypot.

---

## 7. Standards (short-answer question)

**Definition (ISO/IEC Guide 2:2004):** a standard is "a document, established by consensus, that provides rules, guidelines or characteristics for activities or their results." The Biometric Consortium: "a general set of rules to which all complying procedures, products or research must adhere."

**Bodies:** **ISO/IEC** (data formats, performance evaluation, security requirements, privacy guidelines, testing methodologies — e.g. **ISO/IEC 19794** data formats, **24745** biometric information protection, **30107** presentation attack detection) and **NIST** (testing frameworks, accuracy benchmarks, **FRVT** Face Recognition Vendor Test, **FpVTE** Fingerprint Vendor Technology Evaluation).

**Four standard categories — memorise one example each**

| Category | Purpose | Example |
|---|---|---|
| Technical interfaces | Interfaces between biometric components/subsystems, incl. protection of stored and transferred data | ANSI INCITS 358-2002 **BioAPI** v1.1; ANSI INCITS 398-2005 **CBEFF** (Common Biometric Exchange File Format) |
| Data interchange formats | How the biometric data itself is encoded for exchange | INCITS 377-2004 Finger Pattern; **378-2004 Finger Minutiae**; 379-2004 Iris Image |
| Application profiles | Which standards to use together for a given application domain | INCITS 383-2003 Transportation Workers; 394-2004 Border Management |
| Performance testing & reporting | How to test and report accuracy | INCITS 409.1 Principles Framework; 409.2 Technology Testing; 409.3 Scenario Testing |

---

## 8. Physiological biometrics — the compressed table

| Trait | What is measured | Key point for the exam |
|---|---|---|
| **Finger scan** | Friction ridges & valleys; **minutiae** = ridge endings + bifurcations | Sensors: **capacitive** (charge differences, phone/laptop), **optical** (light + high-contrast picture), **ultrasonic** (sound waves, 3D map, works through water/dirt/grease) |
| **Face scan** | ~80 nodal points (eye distance, nose width, eye-socket depth, cheekbones, jaw line, chin) → **faceprint / embedding** | The **only biometric that works without user cooperation**; therefore the biggest privacy risk |
| **Iris scan** | Texture of the coloured ring — furrows, crypts, freckles; encoded as an IrisCode | Extremely high accuracy, stable through life, low FNMR; needs cooperation and costs more |
| **Retina scan** | Blood-vessel pattern at the back of the eye, via low-intensity IR | Most accurate and hardest to spoof; most **intrusive** and least accepted |
| **Ear scan** | Shape and geometry of the outer ear (helix, lobe) | Passive like face, less affected by expression |
| **Palm print** | Principal lines, wrinkles, ridges of the palm; far larger area than a fingertip | More minutiae ⇒ higher accuracy; used in forensics with latent palm prints |
| **Hand vascular geometry** | Subcutaneous vein pattern under **infrared / NIR** imaging | Internal trait ⇒ hard to spoof, needs a live hand; affected by age, temperature, activity |
| **Knuckle** | Finger-knuckle-surface texture patterns | Pipeline: **weighted median filter** for noise → knuckle-region extraction by **variational approach** |
| **DNA** | Polymorphic sequence markers | "Intrinsically digital"; most reliable; **does not change during life or after death**; but not real-time, needs a physical sample, huge privacy load. Used in forensics and paternity testing |
| **Dental** | Dental radiographs: tooth contours, relative positions, dental work (crowns, fillings, bridges) | Two stages: feature extraction (**anisotropic diffusion** enhancement + **Mixture of Gaussians** segmentation of dental work), then matching (tooth-level shape registration → image distances → subject identification). Post-mortem vs ante-mortem forensic identification |
| **Cognitive — EEG** | Electrical activity of neurons via scalp electrodes, **10–20 placement system**, sampled 0.5–1.0 kHz | Chain: electrodes + conductive media → amplifiers with filters → A/D converter → recording device. Generates hundreds of MB per session |
| **Cognitive — ECG** | Electrical activity of the heart | Three named advantages: **(1) inherent liveness** — only obtainable from a living person, **(2) high security** — no technology yet exists to counterfeit it, **(3) combined information** — identity + cardiac condition + emotional/physical state |

---

## 9. Behavioral biometrics — the compressed table

| Trait | Static / raw signal | Dynamic / distinguishing feature |
|---|---|---|
| **Signature scan** | **Static mode**: signature written on paper, scanned, recognised by *shape only* | **Dynamic mode**: written on a digitizing tablet, captures **shape, speed, stroke order, pen pressure, timing** in real time — far harder to forge |
| **Keystroke scan** ("keystroke dynamics") | Timing of key press/release on keyboards, phones, touch panels | **Dwell time** = how long a key is held; **flight time** = interval between keystrokes. Software-only, no extra hardware |
| **Voice scan** | Waveform from a microphone, landline or mobile | Combines behavioral *and* physiological: **vocal-tract shape** (physiological) + **what is said and how** (behavioral) |
| **Gait recognition** | Video of walking | Binary silhouette extracted → contours/segmentation → feature extraction distinguishing one gait from another. Works at a distance, no cooperation |
| **Gesture recognition** | Hand/body motion | Two approaches: **glove-based** (sensor glove measures hand directly) and **vision-based** (camera) — the latter splits into **appearance-based** (2D image features) and **3D hand-model-based** (kinematic model, joint angles) |

**Voice scan vs speech recognition — a near-certain question.** Speaker/voice recognition answers **WHO is speaking** (tone, pitch, accent) and is authentication. Speech recognition answers **WHAT was said** and is transcription; used in hands-free computing, map and menu navigation. In a phone banking flow, speech recognition turns the spoken digits into an account number; voice-scan checks the vocal characteristics against that account.

**Voice-scan weaknesses to list:** more susceptible to **replay attacks** than other biometrics; accuracy hurt by low-quality capture devices and ambient noise; PC deployment requires users to form new habits; **large template size** limits the applications it fits.

**Speaker-dependent vs speaker-independent:** dependent systems are trained on one user's voice characteristics (more robust, less convenient, less portable, good when there is only one user); independent systems recognise many users by *restricting the context* — limited words and phrases — and need no per-user training, which is why automated telephone interfaces use them.

**Gesture taxonomy:** *static* gestures — hand position does not change, meaning carried by finger shape and flexure angles; *dynamic* gestures — position changes over time in three phases **preparation → stroke → retraction**, with the message carried by the temporal sequence of the stroke phase. Interface-level split: *offline* gestures (processed after interaction, e.g. activating a menu) vs *online* gestures (direct manipulation, e.g. scale or rotate).

**Three levels of gesture recognition:** **Detection** (segment image, find hand edges/position) → **Tracking** (frame-by-frame, using magnetic, optical, acoustic, inertial or mechanical trackers) → **Recognition** (feature extraction + classification, gesture class declared and the associated action performed).

---

## 10. The security-threat table (fingerprint pipeline) — high-value answer

Learn the *shape*: one threat per pipeline stage. It generalises to face, gesture, any modality.

| Stage | Threat | Vulnerability | Impact | Countermeasure |
|---|---|---|---|---|
| Sensor | **Spoofing / presentation attack** | Fake finger — silicone, gelatin, latex, 3D print | Unauthorised access | **Liveness detection**: multi-spectral sensing, pulse detection, sweat-pore detection, temperature sensing |
| Sensor | **Replay attack** | Replaying a previously captured fingerprint image | Bypass authentication | Nonces, timestamps, challenge–response, session-specific prompts |
| Preprocessing | **Adversarial image attack** | Maliciously perturbed input image | Incorrect feature extraction | Adversarial training, input validation |
| Feature extraction | **Feature manipulation** | Altering minutiae points | False match or false reject | Integrity protection, signed feature vectors |
| Communication | **Man-in-the-middle** | Intercepting fingerprint data in transit | Data theft or modification | TLS, encryption, mutual authentication, integrity checks |
| Template database | **Template theft** | Stealing stored templates | Identity theft | Cancellable biometrics, template encryption/hashing |
| Template database | **Template modification** | Inserting or altering templates | Unauthorised enrolment | Access control, audit logging, signed templates |
| Matcher | **Hill-climbing attack** | Repeatedly tweaking the input until the score crosses threshold | System compromise | Hide scores, rate-limit attempts, lockout |
| Decision module | **Decision override** | Modifying the accept/reject result | Unauthorised access | Secure execution, signed decisions |
| Whole system | **Insider attack** | Administrator misuse | Data leakage | Separation of duties, logging, least privilege |

---

## 11. Modern-systems facts worth one bonus mark

- **FIDO2 / WebAuthn** — decentralised architecture: the biometric never leaves the device. Components: **Relying Party** (server that validates signatures), **WebAuthn API** (browser/OS JavaScript API), **Authenticator** (internal — Apple Secure Enclave, Android Keystore; or external — YubiKey), **CTAP2** (client-to-authenticator protocol over USB/NFC/BLE). Bank-login flow: local face match releases the private key from the secure enclave, which signs the server's challenge. Two advantages: **phishing-proof** (key bound to app ID/domain) and **zero-trust biometrics** (server never sees facial data). Contrast: a college attendance system needs a **centralised 1:N** model instead.
- **Continuous / behavioral authentication** — point-in-time login verifies *a moment, not a person*; credentials are portable, sessions are hijackable, users can be coerced. Behavioral signals therefore feed a **per-action risk score** that triggers step-up challenges, rather than a binary allow/deny. Operational problems: **cold start** (template needs enough genuine sessions), **drift** (behavior changes with device, injury, fatigue ⇒ scheduled re-enrolment), context normalisation across device classes, and false-positive economics.
