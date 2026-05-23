import re
import subprocess
from pathlib import Path

REPO = Path(r"C:\Users\sster\Documents\Github\UE5_DEEPSLEEP")
SOURCE_ROOT = REPO / "Source"

MOVED_PREFIXES = {
    "Source/DEEPSLEEP/AI/": "Source/DEEPSLEEP/Variant_Combat/AI/",
    "Source/DEEPSLEEP/Animation/": "Source/DEEPSLEEP/Variant_Combat/Animation/",
    "Source/DEEPSLEEP/Gameplay/": "Source/DEEPSLEEP/Variant_Combat/Gameplay/",
    "Source/DEEPSLEEP/Interfaces/": "Source/DEEPSLEEP/Variant_Combat/Interfaces/",
    "Source/DEEPSLEEP/UI/": "Source/DEEPSLEEP/Variant_Combat/UI/",
}

EXACT = {
    "Copyright Epic Games, Inc. All Rights Reserved.": "에픽게임즈의 모든 권리 보유.",
    "Fill out your copyright notice in the Description page of Project Settings.": "프로젝트 설정의 설명 페이지에서 저작권 고지를 작성하세요.",
    "Constructor": "생성자",
    "Default constructor": "기본 생성자",
    "Cleanup": "정리 작업",
    "Initialization": "초기화",
    "Gameplay initialization": "게임플레이 초기화",
    "EndPlay cleanup": "종료 시 정리 작업",
    "Simple GameMode for a third person game": "3인칭 게임용 단순 게임 모드",
    "Basic PlayerController class for a third person game": "3인칭 게임용 기본 플레이어 컨트롤러 클래스",
    "Concrete playable character that owns camera, input bindings and player-only movement helpers.": "카메라, 입력 바인딩, 플레이어 전용 이동 보조 기능을 소유하는 실제 플레이 가능 캐릭터입니다.",
    "Jetpack Movement Component - Pragmata-style jetpack system": "제트팩 이동 컴포넌트 - 프래그마타 스타일 제트팩 시스템",
    "Provides thrust-based aerial movement and burst dodge capability": "추력 기반 공중 이동과 버스트 회피 기능을 제공합니다.",
    "Weapon Manager Component - Manages multiple energy weapons for the player": "무기 관리 컴포넌트 - 플레이어의 여러 에너지 무기를 관리합니다.",
    "Handles weapon switching, equipping, and provides access to active weapon": "무기 전환과 장착을 처리하고 현재 활성 무기에 접근할 수 있게 합니다.",
    "Energy Weapon Types - Pragmata-style energy weapons": "에너지 무기 종류 - 프래그마타 스타일 에너지 무기",
    "Energy Weapon Damage Types": "에너지 무기 피해 유형",
    "A basic life bar user widget.": "기본 라이프 바 사용자 위젯입니다.",
    "A simple player-controllable third person character": "플레이어가 조작하는 단순한 3인칭 캐릭터",
    "Implements a controllable orbiting camera": "조작 가능한 궤도 카메라를 구현합니다.",
    "A basic Actor in charge of spawning Enemy Characters and monitoring their deaths.": "적 캐릭터를 생성하고 그들의 사망을 감시하는 기본 액터입니다.",
    "Enemies will be spawned one by one, and the spawner will wait until the enemy dies before spawning a new one.": "적은 하나씩 생성되며, 스포너는 현재 적이 죽을 때까지 기다렸다가 새 적을 생성합니다.",
    "The spawner can be remotely activated through the ICombatActivatable interface": "스포너는 전투 활성화 가능 인터페이스를 통해 원격으로 활성화될 수 있습니다.",
    "When the last spawned enemy dies, the spawner can also activate other ICombatActivatables": "마지막 적이 죽으면 스포너는 다른 전투 활성화 가능 액터도 활성화할 수 있습니다.",
    "A simple volume that activates a list of actors when the player pawn enters.": "플레이어 폰이 들어오면 액터 목록을 활성화하는 단순 볼륨입니다.",
    "A simple physics box that reacts to damage through the ICombatDamageable interface": "전투 피해 가능 인터페이스를 통해 피해에 반응하는 단순 물리 박스입니다.",
    "A simple invincible combat training dummy": "단순한 무적 전투 훈련용 더미입니다.",
    "A basic actor that applies damage on contact through the ICombatDamageable interface.": "전투 피해 가능 인터페이스를 통해 접촉 시 피해를 주는 기본 액터입니다.",
    "Interactable Interface": "상호작용 가능 인터페이스",
    "CombatAttacker Interface": "전투 공격자 인터페이스",
    "CombatDamageable interface": "전투 피해 가능 인터페이스",
    "Basic EnvQuery Context that returns the first local player": "첫 번째 로컬 플레이어를 반환하는 기본 환경 질의 컨텍스트",
    "Returns the enemy character's last known danger location": "적 캐릭터의 마지막 위험 위치를 반환합니다.",
    "StateTree Component": "상태 트리 컴포넌트",
    "Completed attack animation delegate for StateTree": "상태 트리용 공격 애니메이션 완료 델리게이트",
    "Landed delegate for StateTree": "상태 트리용 착지 델리게이트",
    "Enemy died delegate": "적 사망 델리게이트",
    "An AI-controlled character with combat capabilities.": "전투 능력을 가진 인공지능 제어 캐릭터입니다.",
    "Its bundled AI Controller runs logic through StateTree": "내장된 인공지능 컨트롤러가 상태 트리를 통해 로직을 수행합니다.",
    "A simple volume that activates a list of actors when the player pawn enters.": "플레이어 폰이 들어오면 액터 목록을 활성화하는 단순 볼륨입니다.",
    "A basic Actor in charge of spawning Enemy Characters and monitoring their deaths.": "적 캐릭터를 생성하고 그들의 사망을 감시하는 기본 액터입니다.",
    "AnimNotify to perform a charged attack hold check.": "차지 공격 홀드 여부를 검사하는 애님 노티파이입니다.",
    "AnimNotify to perform a combo string check.": "콤보 연계 여부를 검사하는 애님 노티파이입니다.",
    "AnimNotify to tell the actor to perform an attack trace check to look for targets to damage.": "액터에게 공격 추적 검사를 수행해 피해 대상을 찾도록 알리는 애님 노티파이입니다.",
    "Fast fire, low damage": "빠른 연사, 낮은 피해",
    "Medium range AoE": "중거리 광역 공격",
    "Melee high damage": "근접 고피해",
    "Stun/area control": "기절 및 범위 제어",
    "Allows reaction to incoming attacks": "들어오는 공격에 반응할 수 있게 합니다.",
    "Set to true after use to avoid accidentally resetting the checkpoint": "실수로 체크포인트를 다시 설정하지 않도록 사용 후 true로 설정합니다.",
    "No other weapons to switch to": "전환할 다른 무기가 없습니다.",
    "Already using this weapon": "이미 이 무기를 사용 중입니다.",
    "Energy weapons are client-side only for now": "현재 에너지 무기는 클라이언트 전용으로만 동작합니다.",
    "WITH_EDITOR": "에디터 전용",
    "create the StateTree AI Component": "상태 트리 인공지능 컴포넌트 생성",
    "ensure we start the StateTree when we possess the pawn": "폰을 빙의할 때 상태 트리가 시작되도록 설정",
    "ensure we're attached to the possessed character.": "빙의한 캐릭터에 연결되도록 설정",
    "this is necessary for EnvQueries to work correctly": "이는 환경 질의가 올바르게 동작하는 데 필요합니다.",
    "create the box volume": "박스 볼륨 생성",
    "set the box's extent": "박스 크기 설정",
    "set the default collision profile to overlap all dynamic": "기본 충돌 프로필을 모든 동적 오버랩으로 설정",
    "bind the begin overlap": "오버랩 시작 이벤트 바인딩",
    "ensure we use this only once": "이 기능이 한 번만 사용되도록 확인",
    "has the player entered this volume?": "플레이어가 이 볼륨에 들어왔는가?",
    "raise the checkpoint used flag": "체크포인트 사용 플래그 설정",
    "update the player's respawn checkpoint": "플레이어의 리스폰 체크포인트 갱신",
    "CreateDefaultSubobject": "기본 서브오브젝트 생성",
    "create the mesh": "메시 생성",
    "set the collision properties": "충돌 속성 설정",
    "enable physics": "물리 활성화",
    "disable navigation relevance so boxes don't affect NavMesh generation": "박스가 내비 메시 생성에 영향을 주지 않도록 내비게이션 관련성을 비활성화",
    "clear the death timer": "사망 타이머 초기화",
    "only process damage if we still have HP": "체력이 남아 있을 때만 피해를 처리",
    "apply the damage": "피해 적용",
    "are we dead?": "사망했는가?",
    "call the BP handler to play effects, etc.": "효과 재생 등을 위해 블루프린트 핸들러를 호출",
    "bind the attack montage ended delegate": "공격 몽타주 종료 델리게이트 바인딩",
    "set the AI Controller class by default": "기본 인공지능 컨트롤러 클래스를 설정",
    "use an AI Controller regardless of whether we're placed or spawned": "배치 여부와 관계없이 인공지능 컨트롤러를 사용",
    "reset HP to maximum": "체력을 최대치로 초기화",
    "call the attack completed delegate so the StateTree can continue execution": "상태 트리가 계속 실행될 수 있도록 공격 완료 델리게이트를 호출",
    "StateTree task to perform a combo attack": "콤보 공격을 수행하는 상태 트리 태스크",
    "StateTree task to perform a charged attack": "차지 공격을 수행하는 상태 트리 태스크",
    "StateTree task to wait for the character to land": "캐릭터의 착지를 기다리는 상태 트리 태스크",
    "StateTree task to get information about the player character": "플레이어 캐릭터 정보를 가져오는 상태 트리 태스크",
    "StateTree task to face an AI-Controlled Pawn towards an Actor": "인공지능 제어 폰이 액터를 향하도록 하는 상태 트리 태스크",
    "StateTree task to face an AI-Controlled Pawn towards a world location": "인공지능 제어 폰이 월드 위치를 향하도록 하는 상태 트리 태스크",
    "StateTree task to change a Character's ground speed": "캐릭터의 지상 속도를 변경하는 상태 트리 태스크",
    "Provides common functionality to trigger attack animation events.": "공격 애니메이션 이벤트를 트리거하기 위한 공통 기능을 제공합니다.",
    "Performs an attack's collision check. Usually called from a montage's AnimNotify": "공격의 충돌 검사를 수행합니다. 보통 몽타주의 애님 노티파이에서 호출됩니다.",
    "Performs a combo attack's check to continue the string. Usually called from a montage's AnimNotify": "콤보 공격이 이어질지 검사합니다. 보통 몽타주의 애님 노티파이에서 호출됩니다.",
    "Performs a charged attack's check to loop the charge animation. Usually called from a montage's AnimNotify": "차지 공격 애니메이션을 반복할지 검사합니다. 보통 몽타주의 애님 노티파이에서 호출됩니다.",
    "Perform the Anim Notify": "애님 노티파이를 수행합니다.",
    "Get the notify name": "노티파이 이름을 반환합니다.",
    "Source bone for the attack trace": "공격 추적의 기준 본",
}

TERM_MAP = {
    "StateTree": "상태 트리",
    "AI Controller": "인공지능 컨트롤러",
    "PlayerController": "플레이어 컨트롤러",
    "GameMode": "게임 모드",
    "Blueprint": "블루프린트",
    "AnimNotify": "애님 노티파이",
    "AnimMontage": "애님 몽타주",
    "EnvQuery Context": "환경 질의 컨텍스트",
    "EnvQuery": "환경 질의",
    "BeginOverlap": "오버랩 시작",
    "TakeDamage": "피해 처리",
    "Landed": "착지",
    "EndPlay": "종료 처리",
    "BeginPlay": "시작 처리",
    "BP": "블루프린트",
    "UMG": "터치 인터페이스",
    "IMC": "입력 매핑 컨텍스트",
    "NavMesh": "내비 메시",
    "Visibility": "가시성",
    "Pragmata": "프래그마타",
    "StateTree AI": "상태 트리 인공지능",
    "AI": "인공지능",
    "Component": "컴포넌트",
    "Context": "컨텍스트",
    "Usually called from a montage's ": "보통 몽타주의 ",
    "common functionality to trigger ": "공통 기능을 제공하여 ",
    " events.": " 이벤트를 트리거합니다.",
    "used": "사용",
    "player's": "플레이어의",
    "box's": "박스",
    "this volume": "이 볼륨",
    "only once": "한 번만",
    "pawn": "폰",
    "when": "때",
    "start": "시작",
    "possess": "빙의",
    "the ": "",
    "ensure ": "",
    "ensure we're ": "",
    "ensure we ": "",
    "jetpack": "제트팩",
    "Jetpack": "제트팩",
    "weapon": "무기",
    "Weapon": "무기",
    "energy": "에너지",
    "Energy": "에너지",
    "damage": "피해",
    "Damage": "피해",
    "thrust": "추력",
    "burst dodge": "버스트 회피",
    "dodge": "회피",
    "dash": "대시",
    "camera": "카메라",
    "widget": "위젯",
    "player": "플레이어",
    "enemy": "적",
    "character": "캐릭터",
    "actor": "액터",
    "actors": "액터들",
    "component": "컴포넌트",
    "input": "입력",
    "mapping context": "매핑 컨텍스트",
    "life bar": "라이프 바",
    "cooldown": "쿨다운",
    "timer": "타이머",
    "loop": "루프",
    "socket": "소켓",
    "trace": "추적",
    "ragdoll": "래그돌",
    "checkpoint": "체크포인트",
    "respawn": "리스폰",
    "flag": "플래그",
    "extent": "크기",
    "profile": "프로필",
    "overlap": "오버랩",
    "dynamic": "동적",
    "local": "로컬",
    "possess": "빙의",
    "started": "시작",
    "ended": "종료",
    "combo": "콤보",
    "charged": "차지",
    "melee": "근접",
    "range": "사거리",
    "area": "영역",
    "control": "제어",
    "trace": "추적",
    "notify": "노티파이",
    "string": "연계",
    "continue": "계속",
    "loop": "반복",
    "check": "검사",
}

PATTERNS = [
    (r"^the (.+)$", r"\1"),
    (r"^create the (.+)$", r"\1 생성"),
    (r"^set the (.+)$", r"\1 설정"),
    (r"^get the (.+)$", r"\1 가져오기"),
    (r"^bind the (.+)$", r"\1 바인딩"),
    (r"^clear the (.+)$", r"\1 초기화"),
    (r"^reset the (.+)$", r"\1 초기화"),
    (r"^update the (.+)$", r"\1 갱신"),
    (r"^apply the (.+)$", r"\1 적용"),
    (r"^raise the (.+)$", r"\1 설정"),
    (r"^schedule the (.+)$", r"\1 예약"),
    (r"^spawn the (.+)$", r"\1 생성"),
    (r"^ensure we (.+)$", r"\1 확인"),
    (r"^ensure we're (.+)$", r"\1 확인"),
    (r"^has the (.+)$", r"\1인가?"),
    (r"^common functionality to trigger (.+)$", r"\1를 트리거하기 위한 공통 기능을 제공합니다."),
    (r"^~Begin (.+) Interface$", r"~\1 인터페이스 시작"),
    (r"^~End (.+) Interface$", r"~\1 인터페이스 종료"),
    (r"^~begin (.+) interface$", r"~\1 인터페이스 시작"),
    (r"^~end (.+) interface$", r"~\1 인터페이스 종료"),
    (r"^Activate (.+)$", r"\1를 활성화합니다."),
    (r"^Deactivate(?:s)? (.+)$", r"\1를 비활성화합니다."),
    (r"^Toggle(?:s)? (.+)$", r"\1를 토글합니다."),
    (r"^Switch to (.+)$", r"\1로 전환합니다."),
    (r"^Get (.+)$", r"\1를 반환합니다."),
    (r"^Check if (.+)$", r"\1 확인"),
    (r"^Handles (.+)$", r"\1를 처리합니다."),
    (r"^Perform(?:s)? (.+)$", r"\1를 수행합니다."),
    (r"^Provide(?:s)? (.+)$", r"\1를 제공합니다."),
    (r"^Return(?:s)? (.+)$", r"\1를 반환합니다."),
    (r"^Set (.+)$", r"\1 설정"),
    (r"^Initialize (.+)$", r"\1 초기화"),
    (r"^Create (.+)$", r"\1 생성"),
    (r"^create (.+)$", r"\1 생성"),
    (r"^set (.+)$", r"\1 설정"),
    (r"^get (.+)$", r"\1 가져오기"),
    (r"^bind (.+)$", r"\1 바인딩"),
    (r"^clear (.+)$", r"\1 초기화"),
    (r"^reset (.+)$", r"\1 초기화"),
    (r"^update (.+)$", r"\1 갱신"),
    (r"^apply (.+)$", r"\1 적용"),
    (r"^spawn (.+)$", r"\1 생성"),
    (r"^schedule (.+)$", r"\1 예약"),
    (r"^raise (.+)$", r"\1 설정"),
]

COMMENT_PATTERNS = [
    re.compile(r"^(?P<indent>\s*)//(?P<space>\s?)(?P<body>.*)$"),
    re.compile(r"^(?P<indent>\s*)/\*\*(?P<space>\s?)(?P<body>.*?)(?P<end>\s*\*/)?$"),
    re.compile(r"^(?P<indent>\s*)\*(?P<space>\s?)(?P<body>.*)$"),
    re.compile(r"^(?P<indent>\s*#endif\s*//)(?P<space>\s?)(?P<body>.*)$"),
]


def git_show(path: str):
    result = subprocess.run(
        ["git", "--no-pager", "show", f"HEAD:{path}"],
        cwd=REPO,
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="ignore",
    )
    return result.stdout if result.returncode == 0 else None


def source_text_for(current_file: Path, current_text: str) -> str:
    rel = current_file.relative_to(REPO).as_posix()
    original = git_show(rel)
    if original is not None:
        return original
    for current_prefix, old_prefix in MOVED_PREFIXES.items():
        if rel.startswith(current_prefix):
            mapped = old_prefix + rel[len(current_prefix):]
            original = git_show(mapped)
            if original is not None:
                return original
    return current_text


def translate_body(body: str) -> str:
    stripped = body.strip()
    if not stripped:
        return body
    if stripped in EXACT:
        return body.replace(stripped, EXACT[stripped], 1)
    if "?" in stripped and re.search(r"[가-힣]", stripped) is None:
        return body
    translated = stripped
    for src, dst in TERM_MAP.items():
        translated = translated.replace(src, dst)
    for pattern, repl in PATTERNS:
        candidate = re.sub(pattern, repl, translated)
        if candidate != translated:
            translated = candidate
            break
    if translated == stripped:
        return body
    return body.replace(stripped, translated, 1)


def translate_line_from_source(current_line: str, source_line: str) -> str:
    for current_regex, source_regex in zip(COMMENT_PATTERNS, COMMENT_PATTERNS):
        current_match = current_regex.match(current_line)
        source_match = source_regex.match(source_line)
        if source_match and current_match:
            translated = translate_body(source_match.group("body"))
            if translated == current_match.group("body"):
                return current_line
            if current_regex.pattern.startswith(r"^(?P<indent>\s*)//"):
                return f"{current_match.group('indent')}//{current_match.group('space')}{translated}" + ("\n" if current_line.endswith("\n") else "")
            if "/\\*\\*" in current_regex.pattern:
                end = current_match.groupdict().get("end") or ""
                return f"{current_match.group('indent')}/**{current_match.group('space')}{translated}{end}" + ("\n" if current_line.endswith("\n") else "")
            if current_regex.pattern.startswith(r"^(?P<indent>\s*)\*"):
                return f"{current_match.group('indent')}*{current_match.group('space')}{translated}" + ("\n" if current_line.endswith("\n") else "")
            return f"{current_match.group('indent')}{current_match.group('space')}{translated}" + ("\n" if current_line.endswith("\n") else "")
    return current_line


def direct_translate_current_line(current_line: str) -> str:
    for regex in COMMENT_PATTERNS:
        match = regex.match(current_line)
        if not match:
            continue
        translated = translate_body(match.group("body"))
        if translated == match.group("body"):
            return current_line
        if regex.pattern.startswith(r"^(?P<indent>\s*)//"):
            return f"{match.group('indent')}//{match.group('space')}{translated}" + ("\n" if current_line.endswith("\n") else "")
        if "/\\*\\*" in regex.pattern:
            end = match.groupdict().get("end") or ""
            return f"{match.group('indent')}/**{match.group('space')}{translated}{end}" + ("\n" if current_line.endswith("\n") else "")
        if regex.pattern.startswith(r"^(?P<indent>\s*)\*"):
            return f"{match.group('indent')}*{match.group('space')}{translated}" + ("\n" if current_line.endswith("\n") else "")
        return f"{match.group('indent')}{match.group('space')}{translated}" + ("\n" if current_line.endswith("\n") else "")
    return current_line


def process_file(path: Path) -> bool:
    current_text = path.read_text(encoding="utf-8", errors="ignore")
    source_text = source_text_for(path, current_text)
    current_lines = current_text.splitlines(True)
    source_lines = source_text.splitlines(True)
    changed = False
    new_lines = []

    if len(current_lines) == len(source_lines):
        for current_line, source_line in zip(current_lines, source_lines):
            translated_line = translate_line_from_source(current_line, source_line)
            if translated_line == current_line:
                translated_line = direct_translate_current_line(current_line)
            if translated_line != current_line:
                changed = True
            new_lines.append(translated_line)
    else:
        for current_line in current_lines:
            translated_line = direct_translate_current_line(current_line)
            if translated_line != current_line:
                changed = True
            new_lines.append(translated_line)

    if changed:
        path.write_text("".join(new_lines), encoding="utf-8", newline="")
    return changed


if __name__ == "__main__":
    changed_files = []
    for path in sorted(SOURCE_ROOT.rglob("*")):
        if path.suffix.lower() not in {".h", ".cpp", ".cs"}:
            continue
        if process_file(path):
            changed_files.append(path.relative_to(REPO).as_posix())
    print("\n".join(changed_files))



