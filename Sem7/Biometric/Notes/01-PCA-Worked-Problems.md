# PCA / Eigenfaces — Worked Problems

This is the most likely numerical question on the paper. The method never changes; only the
numbers do. Learn the seven steps, then run the two worked examples below.

---

## Why PCA at all (the two-mark preamble)

A 100 × 100 grayscale face is **10,000 features**; 500 such faces make a 500 × 10,000 dataset.
Training directly on 10,000-dimensional vectors is computationally expensive, memory intensive,
and highly redundant because **neighbouring pixels are strongly correlated**. PCA projects the
faces onto a small set of directions of maximum variance, keeping most of the information at a
fraction of the dimensionality. It is an **unsupervised, non-parametric** dimensionality-reduction
technique, known in this application as the **Eigenfaces** method (**Turk and Pentland, 1991**).

An **eigenface is not a real face** — it is a mathematical pattern representing one major
direction of variation in facial appearance.

---

## The algorithm — memorise this spine

**Training / initialisation phase**

1. **Flatten** each `n × n` training image row-wise into an `N × 1` column vector (`N = n²`).
2. **Mean face** `μ` — the mean of each component across all training faces.
3. **Normalise**: `φᵢ = Iᵢ − μ`. Arrange the `φᵢ` as columns of matrix `A` (also written `X_c`).
4. **Covariance matrix** `C = (1/(n−1)) · X_cᵀ X_c`.
5. **Eigenvalues and eigenvectors** of `C` from `det(C − λI) = 0`. Sort eigenvalues descending
   and keep the top `k` eigenvectors — these are the **eigenfaces**. Discard the small ones,
   because the large eigenvalues already explain almost all of the variance.
6. **Weights** of every training face: `wᵢ = vᵢᵀ · φ` — one weight per eigenvector per face.
   The set of weight vectors is the **face database**.

**Recognition phase**

7. Flatten the test image → subtract **the same** `μ` → project onto **the same** eigenvectors to
   get its weight vector → compute the **Euclidean distance** to every stored weight vector →
   the **smallest distance** identifies the person (subject to a threshold).

> Exam trap: in step 7 you must reuse the training mean and the training eigenvectors. Never
> recompute a mean from the test image.

---

## Worked Example 1 — the solved class problem

**Training images (2 × 2):**

```
I1 = [1 2 ; 3 4]     I2 = [2 3 ; 4 5]     I3 = [3 4 ; 5 6]     I4 = [4 5 ; 6 7]
```

**Step 1 — flatten row-wise into 4 × 1 column vectors**

```
I1 = (1, 2, 3, 4)ᵀ    I2 = (2, 3, 4, 5)ᵀ    I3 = (3, 4, 5, 6)ᵀ    I4 = (4, 5, 6, 7)ᵀ
```

**Step 2 — mean face** (average each component across the four faces)

```
μ₁ = (1+2+3+4)/4 = 2.5
μ₂ = (2+3+4+5)/4 = 3.5
μ₃ = (3+4+5+6)/4 = 4.5
μ₄ = (4+5+6+7)/4 = 5.5

μ = (2.5, 3.5, 4.5, 5.5)ᵀ
```

**Step 3 — normalise, φᵢ = Iᵢ − μ**

```
φ1 = (−1.5, −1.5, −1.5, −1.5)ᵀ
φ2 = (−0.5, −0.5, −0.5, −0.5)ᵀ
φ3 = ( 0.5,  0.5,  0.5,  0.5)ᵀ
φ4 = ( 1.5,  1.5,  1.5,  1.5)ᵀ
```

Matrix `X_c` = these four as columns:

```
        ⎡ −1.5  −0.5   0.5   1.5 ⎤
X_c  =  ⎢ −1.5  −0.5   0.5   1.5 ⎥
        ⎢ −1.5  −0.5   0.5   1.5 ⎥
        ⎣ −1.5  −0.5   0.5   1.5 ⎦
```

**Steps 4–5 — given in the question.** Eigenvalues `[18, 2, 0.4, 0.1]`. Keep the two largest
(18 and 2); discard 0.4 and 0.1 because they are below 1 and contribute almost no variance.

```
v1 = (0.5,  0.5, 0.5,  0.5)ᵀ        (eigenface 1, for λ = 18)
v2 = (0.5, −0.5, 0.5, −0.5)ᵀ        (eigenface 2, for λ = 2)
```

**Step 6 — weights, w = vᵀφ**

Face 1:
```
w₁ = 0.5(−1.5) + 0.5(−1.5) + 0.5(−1.5) + 0.5(−1.5) = −3
w₂ = 0.5(−1.5) − 0.5(−1.5) + 0.5(−1.5) − 0.5(−1.5) = −0.75 + 0.75 − 0.75 + 0.75 = 0
```

Repeating for the rest gives the **face database**:

| Face | Weight vector |
|---|---|
| I1 | (−3, 0) |
| I2 | (−1, 0) |
| I3 | ( 1, 0) |
| I4 | ( 3, 0) |

Notice the second weight is 0 for every face: all the variation in this dataset lies along the
first eigenface, which is exactly what eigenvalue 18 vs 2 was telling you.

**Step 7 — recognition.** Test face `[2.2 3.2 ; 4.2 5.2]` → vector `(2.2, 3.2, 4.2, 5.2)ᵀ`.

```
φ_test = (2.2−2.5, 3.2−3.5, 4.2−4.5, 5.2−5.5) = (−0.3, −0.3, −0.3, −0.3)ᵀ

w₁ = 0.5(−0.3) × 4 = −0.6
w₂ = 0.5(−0.3) − 0.5(−0.3) + 0.5(−0.3) − 0.5(−0.3) = 0

Test weight vector = (−0.6, 0)
```

Euclidean distances `√[(x₂−x₁)² + (y₂−y₁)²]`:

| Compared with | Computation | Distance |
|---|---|---|
| I1 (−3, 0) | √(−0.6 + 3)² | 2.4 |
| **I2 (−1, 0)** | **√(−0.6 + 1)²** | **0.4 ← smallest** |
| I3 (1, 0) | √(−0.6 − 1)² | 1.6 |
| I4 (3, 0) | √(−0.6 − 3)² | 3.6 |

**Decision:** smallest distance 0.4 ⇒ the test face is recognised as **Face 2 (I2)**.

> Note on the class notes: the handwritten sheet writes `w₁ = 0.6` for the test face, but the
> arithmetic `0.5 × (−0.3) × 4` is **−0.6**, and every distance on the next page is computed
> from −0.6. Write −0.6.

---

## Worked Example 2 — the practice question, fully solved

**Training images (2 × 2):**

```
F1 = [2 1 ; 3 2]     F2 = [3 2 ; 4 3]     F3 = [4 3 ; 5 4]     F4 = [5 4 ; 6 5]
```

Given: largest eigenvalues `[20, 3]`, with

```
v1 = (0.5,  0.5, 0.5,  0.5)ᵀ        v2 = (0.5, −0.5, 0.5, −0.5)ᵀ
```

**(1) Face vectors** — flatten row-wise:

```
F1 = (2, 1, 3, 2)ᵀ    F2 = (3, 2, 4, 3)ᵀ    F3 = (4, 3, 5, 4)ᵀ    F4 = (5, 4, 6, 5)ᵀ
```

**(2) Mean face and normalised vectors**

```
μ₁ = (2+3+4+5)/4 = 3.5
μ₂ = (1+2+3+4)/4 = 2.5
μ₃ = (3+4+5+6)/4 = 4.5
μ₄ = (2+3+4+5)/4 = 3.5

μ = (3.5, 2.5, 4.5, 3.5)ᵀ
```

```
φ1 = (2−3.5, 1−2.5, 3−4.5, 2−3.5) = (−1.5, −1.5, −1.5, −1.5)ᵀ
φ2 = (3−3.5, 2−2.5, 4−4.5, 3−3.5) = (−0.5, −0.5, −0.5, −0.5)ᵀ
φ3 = (4−3.5, 3−2.5, 5−4.5, 4−3.5) = ( 0.5,  0.5,  0.5,  0.5)ᵀ
φ4 = (5−3.5, 4−2.5, 6−4.5, 5−3.5) = ( 1.5,  1.5,  1.5,  1.5)ᵀ
```

**(3) Weight vectors, w = (v1ᵀφ, v2ᵀφ)**

Because `v2` has two `+0.5` and two `−0.5` entries and every `φ` here is a constant vector, the
second weight is 0 in every case.

```
F1: w₁ = 0.5(−1.5)×4 = −3   w₂ = 0    →  (−3, 0)
F2: w₁ = 0.5(−0.5)×4 = −1   w₂ = 0    →  (−1, 0)
F3: w₁ = 0.5( 0.5)×4 =  1   w₂ = 0    →  ( 1, 0)
F4: w₁ = 0.5( 1.5)×4 =  3   w₂ = 0    →  ( 3, 0)
```

**(4) Recognition of the test face** `[3 2 ; 4 3]` → `(3, 2, 4, 3)ᵀ`

```
φ_test = (3−3.5, 2−2.5, 4−4.5, 3−3.5) = (−0.5, −0.5, −0.5, −0.5)ᵀ
w₁ = 0.5(−0.5) × 4 = −1
w₂ = 0
Test weight vector = (−1, 0)
```

Euclidean distances:

| Compared with | Distance |
|---|---|
| F1 (−3, 0) | √(−1+3)² = 2 |
| **F2 (−1, 0)** | **√(−1+1)² = 0 ← smallest** |
| F3 (1, 0) | √(−1−1)² = 2 |
| F4 (3, 0) | √(−1−3)² = 4 |

**Decision:** distance 0 ⇒ the test face is recognised as **Person 2 (F2)** — an exact match, as
expected since the test image is identical to F2.

---

## Other face-recognition algorithms to name (one line each)

Face recognition splits into **feature-based** methods (areas, distances and angles between
facial feature points used as descriptors) and **appearance-based** methods (global properties of
the image intensity pattern; compute basis vectors, project faces onto them, use the projection
coefficients as the representation).

| Method | One-line description |
|---|---|
| **PCA** | Unsupervised; finds directions of maximum **variance**; the Eigenfaces method. |
| **LDA** | Linear Discriminant Analysis — supervised; finds components that **separate classes**. |
| **ICA** | Independent Component Analysis — recovers statistically independent source features mixed linearly in the input. |
| **LFA** | Local Feature Analysis — uses facial **contour lines** from detection to classify line-segment types. |
| Others named in the slides | Correlation filters, manifolds, tensorfaces. |
