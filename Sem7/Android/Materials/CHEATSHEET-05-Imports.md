# Import Blocks — copy-paste

Wrong or missing imports are the biggest time sink in a Compose lab exam. `Alt + Enter`
handles most of them, but these blocks let you paste and move on.

Replace `com.example.myapp` with your package and `MyAppTheme` with your generated theme.

---

## The universal block — covers most tasks

```kotlin
import android.os.Bundle
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.*
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
```

`androidx.compose.runtime.*` pulls in `remember`, `mutableStateOf`, `getValue`, `setValue`
and `Composable` in one line — which is why the `by` delegate "just works" with it.

---

## Minimal — Activity plus a simple screen

```kotlin
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
```

---

## State — the `by` delegate

```kotlin
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
```

Miss `getValue` / `setValue` and `var x by remember { ... }` fails to compile. This is the
single most common error in this course.

For state that survives rotation:

```kotlin
import androidx.compose.runtime.saveable.rememberSaveable
```

---

## MVVM

```kotlin
// CounterViewModel.kt
import androidx.compose.runtime.State
import androidx.compose.runtime.mutableStateOf
import androidx.lifecycle.ViewModel

// CounterScreen.kt
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.lifecycle.viewmodel.compose.viewModel
```

`viewModel` comes from `androidx.lifecycle.viewmodel.compose`, **not** `androidx.lifecycle`.
Requires the `lifecycle-viewmodel-compose` dependency.

---

## Navigation Compose

```kotlin
import androidx.navigation.NavHostController
import androidx.navigation.NavType
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import androidx.navigation.navArgument
```

Note `navArgument` is in `androidx.navigation`, while `NavHost`, `composable` and
`rememberNavController` are in `androidx.navigation.compose`.

---

## Activities and Intents

```kotlin
import android.app.Activity
import android.content.Intent
import android.os.Bundle
import androidx.compose.ui.platform.LocalContext
```

---

## Toast

```kotlin
import android.content.Context
import android.widget.Toast
import androidx.compose.ui.platform.LocalContext
```

---

## Icons

```kotlin
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Add
import androidx.compose.material.icons.filled.ArrowDropDown
import androidx.compose.material.icons.filled.Home
import androidx.compose.material.icons.filled.ShoppingCart
import androidx.compose.material.icons.filled.Star

// back arrows live under AutoMirrored
import androidx.compose.material.icons.automirrored.filled.ArrowBack
```

---

## Lists

```kotlin
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.runtime.mutableStateListOf
```

---

## Gotchas worth memorising

**Material3, not Material.** Always `androidx.compose.material3.*`. If the IDE offers
`androidx.compose.material.*` (no 3), that is the old library — mixing them causes
confusing type errors.

**`Modifier` vs `modifier`.** Capital `Modifier` is the companion you start a chain with;
lowercase `modifier` is your function's parameter. Inside a composable that takes a
`modifier`, apply the parameter to the outermost element and start fresh chains with
`Modifier` for children.

**`dp` vs `sp`.** `.sp` for font sizes, `.dp` for everything else. Both need explicit
imports from `androidx.compose.ui.unit`.

**Wildcards are fine in an exam.** `import androidx.compose.material3.*` is quicker than
listing twenty components and no one will mark you down for it.

**`@OptIn(ExperimentalMaterial3Api::class)`** is needed above composables using
experimental APIs such as `TopAppBar`. The IDE will tell you; add the annotation to the
function.
