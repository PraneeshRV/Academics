# Android Lab Midterm — Start Here

**Exam date:** 31 Aug 2026
**Syllabus:** Activities and their Lifecycle · Android Application Notes 1 · UI Controls 2, 3, 4 · Three Screen Explorer · MVVM

Everything in this syllabus is **Jetpack Compose**, not XML layouts. There is no
`activity_main.xml`, no `findViewById`, no `setContentView(R.layout...)`. If you catch
yourself typing any of those, stop.

---

## Your machine is ready

Verified on this laptop on exam morning:

| Check | Result |
|---|---|
| Android Studio | `/opt/android-studio` (2026.1.3) |
| SDK | `/opt/android-sdk`, platform `android-36.1`, build-tools 36.0.0 / 36.1.0 |
| Emulator | `Pixel_10_Pro` AVD boots, KVM available at `/dev/kvm` |
| Gradle | 9.5, AGP 9.3.1, Kotlin 2.2.10, Compose BOM 2026.02.01 |
| JDK used by Gradle | Adoptium 21 (from `~/.gradle/jdks`) |
| **Clean build** | **17 seconds** |
| Incremental build | 3–8 seconds |
| Install + launch | ~4 seconds |

A full reference app containing every module in the syllabus was built, installed and
driven end-to-end on the emulator with **zero crashes**. It lives at:

```
~/Praneesh/Projects/android-midterm-master
```

Open that project in Android Studio if you want to see any module running.

### One caution about RAM

The laptop has 15 GB and about 2 GB was free with Studio, the emulator and a browser all
running at once. It works, but it is not roomy. **Before the exam, close the browser and
anything else heavy.** Studio plus emulator alone is comfortable.

---

## Exam-day project setup

1. **New Project → Empty Activity** (this template is already Compose).
2. Name it, Language **Kotlin**, Build configuration language **Kotlin DSL**. Finish.
3. Wait for Gradle sync. If it offers "exclude folders", accept.
4. Run once immediately on the emulator to confirm the skeleton works *before* you write
   anything. A broken run at minute 40 is much worse than a broken run at minute 2.

### If the task mentions MVVM, add this dependency first

`gradle/libs.versions.toml`, under `[libraries]`:

```toml
androidx-lifecycle-viewmodel-compose = { group = "androidx.lifecycle", name = "lifecycle-viewmodel-compose", version.ref = "lifecycleRuntimeKtx" }
```

`app/build.gradle.kts`, under `dependencies`:

```kotlin
implementation(libs.androidx.lifecycle.viewmodel.compose)
```

Then **Sync Now**. Without this, `viewModel()` will not resolve.

### If the task mentions navigation between screens

`gradle/libs.versions.toml`:

```toml
[versions]
navigationCompose = "2.7.7"

[libraries]
androidx-navigation-compose = { group = "androidx.navigation", name = "navigation-compose", version.ref = "navigationCompose" }
```

`app/build.gradle.kts`:

```kotlin
implementation(libs.androidx.navigation.compose)
```

---

## The theme name trap

Android Studio generates a theme named after your project. If your project is
`MyLabApp`, the theme is `MyLabAppTheme` and it lives in
`ui/theme/Theme.kt`. Every manual writes a different name (`HelloWorldTheme`,
`UILearnAppTheme`, `Modifier_CafeTheme`, `CounterMVVM3Theme`).

**Use whatever your project actually generated.** If you copy a manual's code verbatim,
the theme name is the first thing that will fail to compile.

---

## Fastest way to fix a red squiggle

`Alt + Enter` on the error → "Import". Compose has hundreds of imports and typing them
by hand wastes time. If `Alt + Enter` offers several options, prefer the one starting
with `androidx.compose.material3` over `androidx.compose.material`.

For the exact import blocks per topic, see `CHEATSHEET-05-Imports.md`.

---

## Common errors and what they actually mean

| Error | Cause | Fix |
|---|---|---|
| `Unresolved reference 'viewModel'` | missing dependency | add `lifecycle-viewmodel-compose`, sync |
| `Unresolved reference 'MyAppTheme'` | copied a manual's theme name | use your project's generated theme |
| `@Composable invocations can only happen from...` | calling a composable from a normal function | mark the caller `@Composable`, or move the call into one |
| `Type 'TextFieldValue' expected` | wrong TextField overload | keep `value` a `String` and `onValueChange` a `(String) -> Unit` |
| `by` doesn't work on state | missing delegate import | add `androidx.compose.runtime.getValue` and `setValue` |
| `Unresolved reference 'R'` | drawable/string not created yet | add the resource, or remove the reference |
| Value resets when you rotate | used `remember` | that is expected — see the MVVM sheet |

---

## Reading list, in the order they build on each other

1. `CHEATSHEET-01-Lifecycle.md` — what an Activity is, and the callback order
2. `CHEATSHEET-02-UI-Controls-and-Widgets.md` — every control, plus modifiers and state
3. `CHEATSHEET-03-MVVM.md` — Model / View / ViewModel
4. `CHEATSHEET-04-Three-Screen-Explorer.md` — moving between screens
5. `CHEATSHEET-05-Imports.md` — copy-paste import blocks

---

## Note on the missing manual

**"Three Screen Explorer" is not in this Materials folder.** The other five PDFs are all
here; that one was never saved. `CHEATSHEET-04` therefore covers the topic **both ways** —
Navigation Compose (`NavHost`, which is what a Compose course almost certainly used) and
Activities with Intents. Skim the Intent half; learn the NavHost half properly. If you can
still get the manual from a classmate before the exam, do that and check it against the sheet.
