# Ryntra Language Specification

**Version 0.0.1 | State: Working Draft**

**Date: 2026-08-21 | Author: Ryan Almond**

****

## 0. Introduction [intro]

Ryntra is a general-purpose programming language designed to explore
a distinct point in the design space of programming languages.

Ryntra is not intended to replace C, C++, C#, Rust, Java, or any other
existing programming language. It does not attempt to be universally
better than the languages that came before it. Instead, Ryntra exists
to investigate what a general-purpose programming language can look
like when its design is guided by a coherent set of principles.

One of the central principles of Ryntra is explicitness over implicit
behavior. Important semantic decisions should be visible in source
code whenever practical. The language should avoid silently performing
transformations that may obscure programmer intent, while still
permitting implicit behavior where its semantics are predictable and
well-defined.

Ryntra is designed as a general-purpose language. It therefore does
not prescribe a single domain of application. It is intended to provide
the fundamental abstractions required to construct software ranging
from small programs to large and complex systems.

The design of Ryntra is intentionally experimental. Some of its
features may resemble ideas found in existing languages, while others
may deliberately explore different approaches. Similarity to an
existing language is not, by itself, a design goal or a defect. The
purpose is to understand the consequences of different design choices
and to form a language with a coherent identity of its own.

Ryntra is ultimately an attempt to contribute one more point of view
to the history of general-purpose programming languages.

Its success is not defined solely by adoption or popularity. If the
language produces ideas, techniques, or design decisions that are
useful to understand, discuss, preserve, or build upon, then the
project has achieved something meaningful.

****

## 1.1 Terms and Definitions [defs]

### 1.1.1 argument & parameter [defs.anp]

- `argument`: expression in the comma-separated list bounded by parentheses.
- `parameter`: name after the type declaration in the comma-separated list bounded by parentheses.

### 1.1.2 well-formed program & ill-formed program [defs.wifp]

- `well-formed program`: program that follows all the constraints in the specification.
- `ill-formed program`: program that is not well-formed.

****

## 2.1 Lexical Foundation [lex]

### 