# Unit 3 — Behavioral Biometrics

Sources: `Behavioral Biometrics.pdf`, `Behavioral Biometrics2.pdf` (seminar),
`4. Voice Scan.pdf`.

---

## 0. Physiological vs behavioral — the framing table

Physiological biometrics measure **what a body is**. Behavioral biometrics measure **how a person
acts** — passively, continuously, and without an enrolment ceremony.

| | Physiological | Behavioral |
|---|---|---|
| Measures | Fingerprint, face, iris, vein | Typing rhythm, cursor path, swipe, gait |
| Capture | Explicit, at a checkpoint | Passive, throughout the session |
| Friction | User action required | Invisible to the user |
| Revocability | Immutable — cannot be reissued | Template can be **re-enrolled**, and it **drifts** over time |
| Best role | Strong **point-in-time** proof | **Continuous risk signal** and fraud detection |

**The gap behavioral biometrics fills.** Point-in-time authentication assumes one successful
login is enough to trust a session for its whole duration. Credentials, OTPs and even device
binding verify **a moment, not a person**. Three failure modes:

- **Credentials are portable** — phished, purchased or reused passwords transfer perfectly to an
  attacker; the login looks legitimate *because it is*.
- **Sessions are hijackable** — token theft, malware and remote-access tooling put an adversary
  inside an already-trusted session.
- **Users can be coerced** — in scam and social-engineering fraud the genuine user performs the
  transaction under an attacker's direction.

---

## 1. Signature scan

Identifies a person from their handwriting. Two modes:

**1) Static (offline).** The user writes the signature on paper; after writing is complete it is
digitised through an optical scanner or camera. The system recognises the signature by
**analysing its shape** only.

**2) Dynamic (online).** The user signs on a **digitizing tablet**, which acquires the signature
**in real time**, analysing **shape, speed, stroke, pen pressure and timing information during
the act of signing**. Natural and intuitive, so the technology is easy to explain and trust.
Dynamic signature verification uses the behavioral biometrics of a handwritten signature to
confirm the identity of a computer user.

*Why dynamic is the secure one:* a forger can copy the finished shape but not the pressure
profile, stroke order and velocity that produced it — those are not visible in the artifact.

---

## 2. Keystroke scan (keystroke dynamics)

A behavioral biometric using **the unique manner in which a person types**. It is the process of
measuring and assessing typing rhythm on digital devices — computer keyboards, mobile phones,
touch-screen panels. "Keystroke dynamics" refers to the detailed **timing information describing
exactly when each key was pressed and when it was released** as the person types.

**The two raw measurements:**

- **Dwell time** — the duration for which a key is **pressed** (press → release).
- **Flight time** — the duration **between** keystrokes (release of one key → press of the next).

Keystroke dynamics is therefore a **software-based algorithm** measuring both dwell and flight
time to authenticate identity — no additional hardware needed, which is its main deployment
advantage.

*Richer features used in production (seminar deck):* digraph and trigraph latencies, error and
backspace habits, shift-key handedness.

---

## 3. Voice scan

Voice-scan technology uses the distinctive aspects of the voice to **verify the identity of
individuals**.

### Voice scan vs speech recognition — the standard question

| Speaker recognition (voice recognition) | Speech recognition |
|---|---|
| Objective: recognise **WHO** is speaking | Aims at understanding **WHAT** was spoken |
| Identifies a person by analysing **tone, voice pitch and accent** | Used in hands-free computing, map or menu navigation |
| Authentication | Transcription — unrelated to authentication |

Worked contrast: in a phone banking flow, **speech recognition** translates the spoken word into
an **account number**, while **voice-scan verifies the vocal characteristics against those
associated with that account**.

**Voice-scan straddles both categories:** the **shape of the vocal tract** determines to a large
degree how a voice sounds (physiological), while the **user's behavior determines what is spoken
and in what fashion** (behavioral).

### Weaknesses (list these — they are the likely short answer)

- Potentially **more susceptible to replay attacks** than other biometrics.
- Accuracy challenged by **low-quality capture devices and ambient noise**.
- Success as a PC solution requires users to **develop new habits**.
- The **large size of the template** limits the number of potential applications.

### Components

```
Front-end acquisition hardware  →  Local or central processing software
```

Voice-scan systems resemble facial-scan systems in that they **leverage existing acquisition
hardware** and rest primarily on **proprietary software engines** providing template generation
and matching.

- **Hardware:** microphones, landline telephones, mobile phones.
- **Software:** the spoken phrase is converted from analog to digital and transmitted to a local
  or central PC for template generation and storage (enrolment) or template generation and
  matching (verification).

For desktop verification the engine may reside on a local PC, a central PC, or be web-enabled.
In the more common **telephony** applications the engine is either inside the institution the
user is interacting with (e.g. a financial institution) or hosted by a **third party offering
outsourced biometric verification**.

### Pipeline

```
Acquisition → Processing → Distinctive features → Template generation → Template matching
```

**Data acquisition.** Any audio capture device may be used. Performance varies with **audio
signal quality** and with **variation between enrolment and verification devices**, so acquisition
normally takes place on the device likely to be used later. Acquisition is **harder on PCs than
on telephones**, and **harder on mobile phones than on landlines**.

**Data processing.** Before template creation the system eliminates **gaps at the beginning and
end of the recording** so only the passphrase is used, and **filters out non-spoken frequencies**
such as those introduced by telephone lines and microphones.

**Distinctive features.** Voice-scan measures many vocal qualities **not detectable by human
listeners**. Beyond **pitch (fundamental frequency)**, algorithms measure: **gain or intensity,
short-time spectrum of speech, formant frequencies, linear prediction coefficients, cepstral
coefficients, spectrograms (time–frequency–energy patterns), and nasal coarticulation.**

**Template creation.** Generating a voice-scan template usually relies on a **statistics-based
pattern-matching system, most commonly Hidden Markov Models (HMM)** — generalised profiles formed
by comparing multiple samples to find characteristically repeating patterns.

### How it works end to end

At enrolment the user speaks a word or phrase into a microphone to acquire a speech sample. The
electrical signal from the microphone is converted to a digital signal by an **ADC** and recorded
in computer memory as a **digitized sample**. The computer then compares the candidate's input
voice with the stored digitized sample and identifies the candidate.

### Speaker-dependent vs speaker-independent

| Speaker-**dependent** | Speaker-**independent** |
|---|---|
| Relies on knowledge of the candidate's particular voice characteristics, learned through **voice training (enrolment)** | Recognises speech from **different users** by **restricting the context** — limited words and phrases |
| Must be trained to a particular accent and tone before it can recognise what was said | **No per-user training** required |
| More robust, but **less convenient and less portable** | Used for **automated telephone interfaces** |
| Good when only one user will use the system | Good where many individuals use it and per-candidate characteristics need not be recognised |

*Typical training effort:* 5 to 10 minutes of speech is normally enough today; the user is asked
to pronounce key words that let the system infer the accent and voice details, which works
because languages are generally systematic.

### What makes speech hard (background, from the speech-processing slides)

- **Digitization** — analog to digital conversion, sampling and quantizing; filters measure energy
  at points on the frequency spectrum. Knowing the relative importance of frequency bands makes
  this efficient — high-frequency sounds are less informative and can be sampled with broader
  bandwidth (log scale).
- **Signal processing** — separating speech from background noise, e.g. **noise-cancelling
  microphones** (two mics, one facing the speaker and one facing away, since ambient noise is
  roughly equal at both) and **spectrograph analysis** to tell which parts of the signal are
  speech.
- **Phonetics — variability in human speech.** *Between speakers:* vocal range (f0 and pitch
  range), voice quality (growl, whisper, nasality), and **accent** above all. *Within a speaker:*
  health, emotional state, ambient conditions, and speech style (formal read vs spontaneous).
- **Phonology** — distinguishing similar phonemes; differences may be small, showing up in
  **coarticulation effects** and **allophonic variation**.
- **Lexicology and syntax** — disambiguating **homophones** and handling continuous speech.
  Systems can only recognise words in their **lexicon**, so limiting the lexicon is the obvious
  ploy; a **grammar** helps disambiguate.
- **Syntax and pragmatics** — interpreting prosodic features, and filtering **disfluencies**
  (performance errors).

---

## 4. Gait recognition

**Gait** is the style or manner of walking. Gait recognition uses **video of human gait processed
by computer vision**.

Pipeline: the algorithm recognises the gait, processes the received data, **detects contours and
silhouettes and segments individual human features**; a **feature extraction** algorithm then
distinguishes one gait from another. A **binary image of the person's silhouette** is extracted
from the recording and analysed by vision-based algorithms — **silhouette segmentation simplifies
the task** of processing and mapping a comprehensive image. Algorithms vary in their
requirements: some process video signals, others use **sensor data** (accelerometer/gyroscope).

*Why it matters for security:* like face, it works **at a distance without cooperation**, which
makes it useful for surveillance and equally makes it a privacy concern.

---

## 5. Gesture recognition

**What it is.** Technology using sensors to read and interpret hand movements as commands. In the
automotive industry it lets drivers and passengers control the infotainment system without
touching buttons or screens. Gestures originate from any bodily motion or state, but commonly
from the **face or hand**. Gesture recognition can be considered a way for a computer to
understand **human body language**.

**Definition.** A gesture is an action that has to be **seen by someone else** and has to **convey
some piece of information** — usually a movement of part of the body, especially a hand or the
head, to express an idea or meaning. Gesture recognition technologies are relatively young and
have minimised the need for text interfaces and GUIs.

### Approaches

```
Gesture recognition ─┬─ Glove-based technique
                     └─ Computer-vision based ─┬─ Appearance-based methods
                                               └─ 3D hand-model-based methods
```

- **Glove-based** — a well-known means of recognising hand gestures; a sensor attached to a glove
  **directly measures hand movements**.
- **Vision-based** — the sensor is a **camera**. Split by feature-extraction scheme into:
  - **Appearance-based methods** — use features of the **training image** to model visual
    appearance and compare those parameters with the features of the test image.
  - **3D hand-model-based methods** — rely on a **3D kinematic model**, estimating the **angular
    and linear parameters** of the model.

### 3D model-based hand gesture recognition

Represents the hand as a **three-dimensional kinematic model of bones, joints and fingers**.
Rather than recognising gestures directly from images, it **estimates the hand's 3D pose** by
determining the angular (joint rotations) and linear (position and translation) parameters.

**Hand model:** **palm** (base) + **five fingers** (thumb, index, middle, ring, little) +
**joints** — **MCP** (metacarpophalangeal), **PIP** (proximal interphalangeal), **DIP** (distal
interphalangeal) and thumb joints. Each joint rotates independently, giving the hand its
**degrees of freedom (DoF)**.

**Parameters estimated**
- **Linear:** hand position (x, y, z), translation of the hand, palm location.
- **Angular:** joint bending angles, finger orientations, wrist rotation, finger articulation.

Together these define the complete 3D pose.

**Sensors:** RGB camera, stereo camera, **depth camera** (Microsoft Kinect, Intel RealSense),
Leap Motion Controller. Depth sensors improve estimation accuracy by providing **explicit
distance information**.

**Processing chain**

```
Input (RGB / depth / stereo camera)
        ↓
Hand detection & segmentation
        ↓
Feature extraction (hand contour, keypoints, depth)
        ↓
3D kinematic hand model — estimate joint angles & hand position (pose)
        ↓
Gesture classification (open hand, fist, pointing, OK, …)
```

### 2D appearance-based vs 3D model-based

| Feature | 2D appearance-based | 3D model-based |
|---|---|---|
| Representation | Image features | Kinematic hand model |
| Input | RGB image | RGB + depth / stereo |
| Parameters | Shape, contour, texture | Joint angles, rotations, translations |
| Viewpoint robustness | Moderate | High |
| Occlusion handling | Limited | Better |
| Computational cost | Low | High |
| Accuracy | Moderate | High |

### Taxonomy of gestures

Gestures are categorised **by observable features** or **by interpretation**. Under observable
features, classified by **temporal relationship**:

- **Static gestures** — hand position does not change during the gesturing period; they rely
  mainly on the **shape and flexure angles of the fingers**.
- **Dynamic gestures** — hand position changes continuously with time, in **three motion phases:
  preparation → stroke → retraction**. The message is mainly contained in the **temporal sequence
  of the stroke phase**. They rely on hand **trajectories and orientations** in addition to shape
  and finger flex angles.

At interface level, two further types:
- **Offline gestures** — processed **after** the user's interaction with the object; e.g. the
  gesture to activate a menu.
- **Online gestures** — **direct manipulation** gestures, used to scale or rotate a tangible
  object.

### Stages of a gesture recognition system

1. **Data acquisition / gesture image collection** — hand, body or face gestures are recorded and
   classified.
2. **Preprocessing** — edge detection, filtering and normalisation to capture the main gesture
   characteristics and fit the input to the recognition model.
3. **Image tracking** — sensors capture the **orientation and position** of the object performing
   the gesture, using one or more trackers: **magnetic, optical, acoustic, inertial or
   mechanical**.
4. **Recognition** — after feature extraction, identified features are stored/processed using
   complex **neural networks or decision trees**, and the command or meaning of the gesture is
   declared; the classifier attaches every test movement to its gesture class.

**Three basic levels** (compressed version of the same idea): **Detection** — a camera detects
hand or body movement and an ML algorithm segments the image to find hand edges and positions;
**Tracking** — the device monitors movement frame by frame; **Recognition** — the system matches
patterns, interprets the gesture and performs the associated action.

### Applications

Talking to computers; **medical operations** — controlling resource distribution in hospitals,
interacting with medical instrumentation, controlling visualisation displays, and helping
handicapped users in rehabilitation therapy; **gesture-based gaming control**, where the
"fast-response" requirement means computer-vision algorithms must be robust *and* efficient,
unlike inspection systems with no real-time requirement where recognition performance dominates;
**home appliance control** — MP3 player, TV.

### Security and privacy of 3D gesture systems

Because these systems are used for authentication, access control, VR/AR, healthcare, robotics
and HCI, they carry a broad attack surface.

| Vulnerability | Description | Impact |
|---|---|---|
| Presentation (spoofing) attack | 3D printed hand, silicone hand, or replayed 3D gesture | Unauthorised authentication |
| Replay attack | Previously recorded RGB/depth gesture sequences replayed | Bypass authentication |
| Adversarial attack | Crafted perturbations make the AI model misclassify | Wrong recognition, unauthorised actions |
| Sensor spoofing | Fake depth or RGB data injected into the camera pipeline | Incorrect pose estimation |
| Depth map manipulation | Projected infrared patterns or fake point clouds | Incorrect 3D reconstruction |
| Occlusion attack | Deliberately hiding fingers or palm | Recognition failure or misclassification |
| Model poisoning | Malicious samples during training, especially federated learning | Reduced accuracy or hidden backdoors |
| Backdoor attack | A gesture trigger forces attacker-chosen outputs | Unauthorised system behaviour |
| Data poisoning | Incorrectly labelled gesture datasets | Reduced reliability |
| Model extraction | Queries approximate or steal the model | IP theft |
| Membership inference | Determines whether a person's data was in training | Privacy leakage |
| Gesture injection | Artificial skeletal data injected into the pipeline | False recognition |
| Communication attack | Gesture data intercepted or modified in transit | Tampering and privacy breach |
| Denial of service | Flooding with gestures or malformed sensor input | System unavailability |

**Privacy vulnerabilities** — even though only hand movements are captured, they can reveal:
biometric identity leakage, behavioral profiling, **health-condition inference (tremors,
arthritis)**, finger length and palm geometry, cross-session user tracking, and activity
inference from gesture patterns.

**AI-specific vulnerabilities** (models are CNNs, Transformers or Graph Neural Networks):
1. **Adversarial examples** — small imperceptible perturbations to depth maps or images fool the
   classifier (thumbs-up predicted as stop).
2. **Backdoor attacks** — a trigger inserted during training, e.g. whenever a small ring is worn
   the model always predicts "Authorized User".
3. **Model inversion** — attacker reconstructs hand shape or gesture patterns from model outputs.
4. **Membership inference** — determines whether a person's gesture data was in the training set.

**Sensor-level attacks:** infrared interference with depth cameras, laser projection corrupting
depth measurements, camera blinding with strong light, fake skeletal-joint generation, time
synchronisation attacks across multiple cameras.

**Network-level attacks** (when data goes to cloud or edge): MitM, packet injection, packet
replay, session hijacking, eavesdropping.

**Hardware vulnerabilities:** camera tampering, sensor replacement, calibration attacks, firmware
modification, physical damage or obstruction.

**Countermeasures**

| Threat | Defence |
|---|---|
| Spoofing | Liveness detection, multi-modal biometrics (hand + face), **challenge–response gestures** |
| Replay | Session-specific **random gesture prompts**, timestamps, nonces |
| Adversarial | Adversarial training, defensive distillation, input validation |
| Model poisoning | Secure federated learning, robust aggregation (**Krum, FedMedian**), anomaly detection |
| Backdoor | Backdoor detection, dataset sanitisation, trigger removal |
| Sensor spoofing | **Sensor fusion** (RGB + depth + IMU), consistency checks |
| Communication | TLS, encryption, authentication, integrity protection |
| Privacy leakage | Differential privacy, federated learning, secure enclaves, homomorphic encryption |
| Model theft | Query rate limiting, watermarking, API authentication |
| DoS | Input validation, rate limiting, resource monitoring |

---

## 6. Video face and mapping the body technology

The class deck sets these as **Assignment 2** rather than lecturing them, so treat the following
as the working definitions.

**Video face.** Face recognition applied to a **continuous video stream** instead of a still
image. The differences that matter:

- The system must **detect and track** a face across frames, then **select the best frame(s)** —
  most frontal, best-lit, in-focus — before matching, since most frames are unusable.
- Multiple frames allow **score fusion over time**, raising accuracy above any single frame, and
  supply natural **liveness evidence** (blinking, micro-movement, 3D parallax from head motion) —
  a printed photo does not move consistently.
- It is the modality behind **surveillance and watchlist screening**: non-cooperative, covert,
  1:N, and therefore the sharpest privacy problem in the syllabus.
- Constraints: pose, illumination and expression variation, motion blur, low CCTV resolution, and
  the compute cost of running detection on every frame.

**Mapping the body technology.** The broader family that treats the **whole body as the
measurable surface** rather than one isolated trait — body-shape and anthropometric measurement,
silhouette and skeletal joint mapping (as in gait and 3D gesture above), and full-body scanning.
Its properties:

- **At-a-distance and non-cooperative** — like face and gait, it needs no presentation ritual.
- **Soft rather than hard biometrics** — height, build and limb proportions are not unique enough
  to identify alone, so they are used to **narrow the candidate set** or to fuse with a hard trait.
- Used for continuous re-identification across camera networks, for **body-worn and wearable**
  sensing, and in AR/VR motion capture.
- The same privacy critique as gait applies with more force: the body can be mapped without
  consent, and the map leaks health, gender and age information.

---

## 7. Continuous authentication (seminar material)

### From raw events to a decision

```
01 Capture   →   02 Extract   →   03 Represent
```

- **Capture** — event stream from an SDK or JS agent, timestamps at **millisecond resolution**,
  **sampling without keylogging content**.
- **Extract** — *statistical* (mean, variance, percentiles), *temporal* (n-gram latencies,
  sequences), *spatial* (curvature, jerk, angular change).
- **Represent** — fixed-length feature vectors per window, normalisation for device and context,
  embeddings from sequence encoders.

**Design constraint:** features must be **discriminative across users, stable within a user, and
cheap enough to compute at session speed.**

### Modelling approaches

| Approach | Detail |
|---|---|
| Distance & statistical | Manhattan / Mahalanobis scoring against the enrolled template. Cheap, interpretable, **weak against skilled mimicry** |
| Classical ML | SVM, random forest, k-NN on engineered features. Strong baselines; needs negative samples or synthetic impostors |
| One-class / anomaly | Autoencoders, isolation forests, one-class SVM. Trained **only on the genuine user** — the realistic production setting |
| Deep sequence models | RNN, LSTM, temporal CNN, transformers over raw event streams. Best accuracy, highest data and latency cost |
| Multimodal fusion | Score- or feature-level fusion of keystroke, mouse, touch and motion. **Consistently outperforms any single modality** |

**Model drift is the operational problem:** typing behavior changes with device, injury, fatigue
and time, so templates need **scheduled re-enrolment**.

### Architecture

```
01 Login → 02 Signal stream (passive capture) → 03 Risk score (per action)
   → 04 Step-up challenge on score drop → 05 Forced reauth at threshold
```

- **Zero Trust fit:** continuous verification replaces the implicit trust granted after a single
  successful login.
- **Standards status:** **NIST SP 800-63B does not yet codify continuous authentication**;
  risk-based reauthentication sits *alongside* AAL, not in place of it.
- **Latency budget:** scoring must return **inside the request path — tens of milliseconds** — or
  it will be bypassed.

### Which signal exposes which attack

| Attack pattern | Dominant tell | Primary modality |
|---|---|---|
| Credential stuffing at scale | Identical timing across sessions and accounts | Keystroke + mouse |
| Human-operated takeover | Template mismatch on familiar fields | Keystroke + touch |
| Remote access tooling | Latency artifacts, non-native cursor motion | Mouse dynamics |
| Coerced / scam-driven transfer | Long hesitation, off-pattern navigation, re-reading | Session behavior |
| Synthetic identity onboarding | Pasted PII, corrections in own-name fields | Form interaction |

**No single signal is decisive** — production systems fuse behavior with device, network and
consortium risk intelligence before acting.

### Deployment realities

- **Cold start** — a template needs enough genuine sessions before it can score; plan a
  shadow-mode period **per user**, not per deployment.
- **Drift and re-enrolment** — accuracy degrades measurably without adaptive templates.
- **Context normalisation** — desktop, mobile and tablet produce incompatible feature
  distributions; score per device class or normalise explicitly.
- **Edge vs cloud scoring** — on-device inference limits data egress and helps privacy posture;
  central scoring gives cross-account intelligence.
- **False-positive economics** — every point of FRR converts to abandoned sessions and call-centre
  load; measure it as a **business cost**, not a model metric.
- **Adversarial robustness** — synthetic input generators and replay of captured event streams are
  the emerging attack surface; test against them.

### Privacy and compliance

| Regime | Obligation |
|---|---|
| **GDPR Article 9** | Behavioral data used to uniquely identify a person is **special-category**; needs an explicit legal basis and, in practice, a **DPIA** |
| **Illinois BIPA** | Carries a **private right of action** — the highest litigation exposure of any biometric regime; written consent and a published retention schedule |
| **CCPA / CPRA** | Biometric identifiers are **sensitive personal information**, with limitation and deletion rights |
| **EU AI Act** | Additional obligations for high-risk biometric systems as provisions phase in |

**Engineering principles:** store **templates, never raw content**; capture **timing, not
keystroke text**; minimise, retain briefly, honour deletion.

### Four takeaways

1. **It is a risk signal, not a gate** — behavior belongs in a score that drives step-up, not a
   binary allow/deny on its own.
2. **Fusion beats single modality** — combine keystroke, pointer, touch and motion, and combine
   those with device and network context.
3. **Tune to the business, then measure** — set the threshold from fraud appetite and friction
   tolerance; track EER, but manage **FRR as a revenue metric**.
4. **Build privacy in at capture** — timing over content, templates over raw streams, short
   retention, documented legal basis.
