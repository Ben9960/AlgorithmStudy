package FerociousFalcon;
import robocode.*;
import robocode.AdvancedRobot;
import robocode.HitWallEvent;
import robocode.ScannedRobotEvent;
import robocode.util.Utils;

public final class FerociousFalcon extends AdvancedRobot {

    private static final int SEQUENCE_LENGTH = 35;
    private static final double INTERVAL_CHANGE = 0.92;
    private static final double TARGET_DISTANCE = 180d;
    private static final double SHOOTING_POWER = 2.4433565d;
    private static final double PROJECTILE_SPEED = 12.5d;
    private static final double DISTANCE_ERROR = 0.38435d;
    private static final double DISTANCE_REGULATOR = 237.5;
    private static final double SPEED_FACTOR = 17.78456345d;

    private static final int BULLETS_TO_FIRE = (int) (TARGET_DISTANCE / PROJECTILE_SPEED + 2);
    private static int moveDirection = 100;

    private static String opponentMovementHistory = "";

    public void run() {
        setAdjustGunForRobotTurn(true);
        turnRadarRightRadians(Double.POSITIVE_INFINITY);
    }

    public void onScannedRobot(ScannedRobotEvent e) {
        int sequenceLength = SEQUENCE_LENGTH;
        double relativeAngle;
        double distance;
        int matchPosition;

        setTurnRadarLeftRadians(getRadarTurnRemaining());

        setTurnRightRadians(
            Math.cos(relativeAngle = e.getBearingRadians())
            - Math.signum(getVelocity() * (distance = e.getDistance()) - TARGET_DISTANCE) * DISTANCE_ERROR
        );

        setTurnRightRadians(
            Math.cos(relativeAngle = e.getBearingRadians())
            - (distance - TARGET_DISTANCE) * getVelocity() / DISTANCE_REGULATOR
        );

        setAhead(moveDirection);

        if (Math.random() > INTERVAL_CHANGE) {
            onHitWall(null);
        }

        int i;
        opponentMovementHistory = String.valueOf(
            (char) Math.round(2 * (e.getVelocity() * Math.sin(e.getHeadingRadians() - (relativeAngle += getHeadingRadians()))))
        ).concat(opponentMovementHistory);

        for (; (matchPosition = opponentMovementHistory.indexOf(opponentMovementHistory.substring(0, sequenceLength--),
        i = (int) (((distance = e.getDistance()) / 12.5D) - 1))) < 0; ) ;

        do {
            relativeAngle += Math.asin((short) opponentMovementHistory.charAt(--matchPosition) / distance / 2d);
        } while (--i > 0);

        setTurnGunRightRadians(Utils.normalRelativeAngle(relativeAngle - getGunHeadingRadians()));

        setFire(SHOOTING_POWER);
    }

    public void onHitWall(HitWallEvent e) {
        moveDirection = -moveDirection;
    }
}
